#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include <vector>
#include <functional>
#include <stdexcept>
#include <optional>

template <typename Key, typename Value>
class LinearProbingHashTable {
private:
    struct KeyValuePair {
        Key key;
        Value value;
        bool isDeleted;

        KeyValuePair(const Key& k, const Value& v)
            : key(k), value(v), isDeleted(false) {}
    };

    std::vector<std::optional<KeyValuePair>> table;
    size_t numElements;
    size_t capacity;
    float loadFactor;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % capacity;
    }

    void rehash() {
        size_t newCapacity = capacity * 2;
        std::vector<std::optional<KeyValuePair>> newTable(newCapacity);

        for (const auto& entry : table) {
            if (entry && !entry->isDeleted) {
                size_t index = std::hash<Key>{}(entry->key) % newCapacity;
                while (newTable[index]) {
                    index = (index + 1) % newCapacity;
                }
                newTable[index] = *entry;
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    LinearProbingHashTable(size_t initialCapacity = 16, float maxLoadFactor = 0.75)
        : table(initialCapacity), numElements(0), capacity(initialCapacity), loadFactor(maxLoadFactor) {}

    void insert(const Key& key, const Value& value) {
        if ((float)numElements / capacity >= loadFactor) {
            rehash();
        }

        size_t index = hash(key);
        while (table[index] && !table[index]->isDeleted) {
            if (table[index]->key == key) {
                table[index]->value = value;
                return;
            }
            index = (index + 1) % capacity;
        }

        table[index] = KeyValuePair(key, value);
        ++numElements;
    }

    bool remove(const Key& key) {
        size_t index = hash(key);
        size_t start = index;

        while (table[index]) {
            if (!table[index]->isDeleted && table[index]->key == key) {
                table[index]->isDeleted = true;
                --numElements;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == start) break; // Avoid infinite loop
        }

        return false;
    }

    Value get(const Key& key) const {
        size_t index = hash(key);
        size_t start = index;

        while (table[index]) {
            if (!table[index]->isDeleted && table[index]->key == key) {
                return table[index]->value;
            }
            index = (index + 1) % capacity;
            if (index == start) break; // Avoid infinite loop
        }

        throw std::runtime_error("Key not found");
    }

    bool contains(const Key& key) const {
        size_t index = hash(key);
        size_t start = index;

        while (table[index]) {
            if (!table[index]->isDeleted && table[index]->key == key) {
                return true;
            }
            index = (index + 1) % capacity;
            if (index == start) break; // Avoid infinite loop
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

#endif // LINEARPROBING_H