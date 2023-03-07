#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

class Dictionary {
    public:
        Dictionary(std::vector<int> keys, int size);

        bool insert(int key, float value);

        int search(int key);
        
        bool remove(int key);

        friend std::ostream& operator<<(std::ostream& os, const Dictionary& obj);
    
    private:
        std::vector<std::pair<int, float>> table;
        int size;
        int count;

        int hash(int key, int probe);
};

int Dictionary::hash(int key, int probe){
    int h1 = key % size;
    int h2 = 1 + (key % (size - 1));
    return (h1 + probe*h2) % size;
}

bool Dictionary::insert(int key, float value){
    if(count == size){
        std::cout << "Error: No open slots left in hash table." << std::endl;
        return false;
    }


    for (size_t i = 0; i < this->size; i++)
    {
        int index = this->hash(key, i);
        auto check_pair = this->table[index];

        if ((check_pair.first == 0 && check_pair.second == 0.0) || (check_pair.first == -1) || (check_pair.first == key))
        {
            this->table[index] = std::make_pair(key, value);
            this->count++;
            return true;
        }
    }

    return false;
}

int Dictionary::search(int key){
    if(this->count == 0) return -1;

    for (size_t i = 0; i < this->size; i++)
    {
        int index = this->hash(key, i);
        auto check_pair = this->table[index];
        if(check_pair.first == 0) return -1;
        if(check_pair.first == key) return index;
    }
    
    return -1;
}

bool Dictionary::remove(int key){
    int index = this->search(key);
    
    if (index >= 0){
        this->table[index] = std::make_pair(-1, 0);
        this->count--;
        return true;
    }

    return false;
    
}

Dictionary::Dictionary(std::vector<int> keys, int size): table(size){
    this->size = size;
    this->count = 0;

    float float_val = 0.1;
    for(int key: keys){
        if(this->size == this->count){
            break;
        }

        this->insert(key, float_val);
        float_val += 0.1;
    }
    
}

std::ostream& operator<<(std::ostream& os, const Dictionary& obj) {
    bool first_char = true;
    for (auto pair : obj.table)
    {   
        // Added in order to avoid trailing whitespace on output
        if(!first_char) os << " ";
        else first_char = false; 

        if((pair.first == 0 && pair.second == 0.0) || (pair.first == -1)) os << "nil";
        else os << "K:" << pair.first << " V:" << pair.second; 

    }
    return os;
}

int main() {
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<int> input_keys;
    int num;
    while (ss >> num) {
        input_keys.push_back(num);
    }

    Dictionary hash(input_keys, 19);
    hash.remove(input_keys[6]);
    hash.insert(input_keys[2], 1.1);
    std::cout << hash << std::endl;
    return 0;
}