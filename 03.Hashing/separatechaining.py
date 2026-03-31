class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class SeparateChainingHashTable:
    def __init__(self, capacity=8, load_factor=0.75):
        self.capacity = capacity
        self.size = 0
        self.table = [None] * capacity
        self.max_load_factor = load_factor

    def _hash(self, key):
        return hash(key) % self.capacity

    def _get_threshold(self):
        # threshold = capacity * load_factor
        return int(self.capacity * self.max_load_factor)

    def insert(self, key, value):
        self._insert(key, value)
        if self.size > self._get_threshold():
            self._rehash()

    def _insert(self, key, value):
        index = self._hash(key)

        if self.table[index] is None:
            self.table[index] = Node(key, value)
            self.size += 1
        else:
            current = self.table[index]
            while current:
                if current.key == key:
                    current.value = value
                    return
                current = current.next
            new_node = Node(key, value)
            new_node.next = self.table[index]
            self.table[index] = new_node
            self.size += 1

    def _rehash(self):
        self.capacity *= 2
        pre_table = self.table
        # reset table and size, then reinsert (so size is correct)
        self.table = [None] * self.capacity
        old_size = self.size
        self.size = 0
        for e in pre_table:
            current = e
            while current:
                # use _insert (which will increment size)
                self._insert(current.key, current.value)
                current = current.next
        # size should equal old_size after reinserting
        assert self.size == old_size

    def search(self, key):
        index = self._hash(key)

        current = self.table[index]
        while current:
            if current.key == key:
                return current.value
            current = current.next

        raise KeyError(key)

    def remove(self, key):
        index = self._hash(key)

        previous = None
        current = self.table[index]

        while current:
            if current.key == key:
                if previous:
                    previous.next = current.next
                else:
                    self.table[index] = current.next
                self.size -= 1
                return
            previous = current
            current = current.next

        raise KeyError(key)

    def __len__(self):
        return self.size

    def __contains__(self, key):
        try:
            self.search(key)
            return True
        except KeyError:
            return False


if __name__ == "__main__":

    # Create a hash table with
    # a capacity of 5
    ht = SeparateChainingHashTable(5)

    # Add some key-value pairs
    # to the hash table
    ht.insert("apple", 3)
    ht.insert("banana", 2)
    ht.insert("cherry", 5)

    # Check if the hash table
    # contains a key
    print("apple?", "apple" in ht)  # True
    print("durian?", "durian" in ht)  # False

    # Get the value for a key
    print("banana:", ht.search("banana"))  # 2

    # Update the value for a key
    ht.insert("banana", 4)
    print("new banana:", ht.search("banana"))  # 4

    ht.remove("apple")
    # Check the size of the hash table
    print("len:", len(ht))  # 3
