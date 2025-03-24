#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Hashable.h"
#include <concepts>
#include <functional> // for std::hash
#include <iostream>
#include <stdexcept>
#include <vector>



template<Hashable T>
class HashTable {

    private:
        static constexpr size_t DEFAULT_NUM_BUCKETS = 10;
        static constexpr float MAXIMUM_LOAD_FACTOR = 0.75f;
        static constexpr float MINIMUM_LOAD_FACTOR = 0.25f;

        size_t buckets;
        std::vector<std::vector<T>> table;

        float load_factor() {
            return static_cast<float>(this->size) / static_cast<float>(this->buckets);
        }

        void rehash(size_t new_num_buckets) {
            std::vector<std::vector<T>> new_table(new_num_buckets);

            for (size_t i = 0; i < this->buckets; i++) {
                for (T& element : table[i]) {
                    size_t index = std::hash<T>{}(element) % new_num_buckets;
                    new_table[index].push_back(element);
                }
            }

            this->table = std::move(new_table);
            this->buckets = new_num_buckets;
        }

    public:

        size_t size;

        HashTable() : buckets(DEFAULT_NUM_BUCKETS), table(DEFAULT_NUM_BUCKETS), size(0) {}
        HashTable(size_t num_buckets) : buckets(num_buckets), table(num_buckets), size(0) {}

        ~HashTable() = default;


        void insert(T value) {
            if (this->load_factor() > MAXIMUM_LOAD_FACTOR) {
                this->rehash(this->buckets * 2);
            }

            size_t index = std::hash<T>{}(value) % this->buckets;
            table[index].push_back(value);
            size++;
        }

        bool contains(T value) {
            size_t index = std::hash<T>{}(value) % this->buckets;
            for (T& element : table[index]) {
                if (element == value) {
                    return true;
                }
            }
            return false;
        }

        bool remove(T value) {

            if (this->load_factor() < MINIMUM_LOAD_FACTOR) {
                this->rehash(this->buckets / 2);
            }

            size_t index = std::hash<T>{}(value) % this->buckets;
            for (auto it = table[index].begin(); it != table[index].end(); it++) {
                if (*it == value) {
                    table[index].erase(it);
                    size--;
                    return true;
                }
            }
            return false;
        }

        void clear() {
            this->table.clear();
            this->table.resize(DEFAULT_NUM_BUCKETS);
            this->size = 0;
            this->buckets = DEFAULT_NUM_BUCKETS;
        }

        void print() {
            for (size_t i = 0; i < this->buckets; i++) {
                std::cout << "Bucket " << i << ": ";
                for (T& element : table[i]) {
                    std::cout << element << "\t";
                }
                std::cout << std::endl;
            }
        }

        size_t num_buckets() {
            return this->buckets;
        }
    
};

#endif // HASHTABLE_H