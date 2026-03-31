#ifndef SEPARATECHAINING_H
#define SEPARATECHAINING_H

#include <vector>
#include <list>
#include <stdexcept>

template <typename Key, typename Value>
class SeparateChainingHashTable {
private:
    struct KeyValuePair {
        Key key;
        Value value;
    };

    std::vector<std::list<KeyValuePair>> table;
    size_t numElements;
    size_t capacity;
    float loadFactor;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % capacity;
    }

    void rehash() {
        size_t newCapacity = capacity * 2;
        std::vector<std::list<KeyValuePair>> newTable(newCapacity);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t newIndex = std::hash<Key>{}(pair.key) % newCapacity;
                newTable[newIndex].push_back(pair);
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    SeparateChainingHashTable(size_t initialCapacity = 16, float maxLoadFactor = 0.75)
        : table(initialCapacity), numElements(0), capacity(initialCapacity), loadFactor(maxLoadFactor) {}

    void insert(const Key& key, const Value& value) {
        if ((float)numElements / capacity >= loadFactor) {
            rehash();
        }

        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;
                return;
            }
        }

        table[index].push_back({key, value});
        ++numElements;
    }

    bool remove(const Key& key) {
        size_t index = hash(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                --numElements;
                return true;
            }
        }

        return false;
    }

    Value get(const Key& key) const {
        size_t index = hash(key);
        const auto& bucket = table[index];

        for (const auto& pair : bucket) {
            if (pair.key == key) {
                return pair.value;
            }
        }

        throw std::runtime_error("Key not found");
    }

    bool contains(const Key& key) const {
        size_t index = hash(key);
        const auto& bucket = table[index];

        for (const auto& pair : bucket) {
            if (pair.key == key) {
                return true;
            }
        }

        return false;
    }

    size_t size() const {
        return numElements;
    }

    bool empty() const {
        return numElements == 0;
    }
};

#endif // SEPARATECHAINING_H
