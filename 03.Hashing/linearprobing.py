class Node:
    def __init__(self, key, x):
        self.key = key
        self.data = x


class DeadNode:
    pass


DEAD = DeadNode()


class LinearProbingHashTable:
    def __init__(self, capacity=8, load_factor=0.5):
        if capacity <= 1:
            raise Exception("hash table size less than 1")
        self.capacity = capacity
        self.load_factor = load_factor
        self.size = 0  # number of stored key/value pairs
        self.hash_table = [None] * self.capacity

    def __repr__(self):
        ret = ""
        for idx, e in enumerate(self.hash_table):
            line = "idx: {}, ".format(idx)
            if e is not None:
                if e is DeadNode:
                    line += "Deadnode"
                else:
                    line += "key: {}, val: {}".format(e.key, e.data)
            else:
                line += "None"
            ret += line + "\n"
        return ret

    def _get_threshold(self):
        return int(self.capacity * self.max_load_factor)

    def _hash_func(self, key):
        return hash(key) % self.capacity

    def _probing_func(self, hash_idx, count):
        # linear probing: wrap with capacity, start count at 0
        return (hash_idx + count) % self.capacity

    def _insert_at(self, idx, node):
        """Place node at index idx and increment count. Internal helper."""
        self.hash_table[idx] = node
        self.size += 1

    def _insert_no_resize(self, key, value):
        """Insert without triggering resize. Honors tombstones."""
        hash_idx = self._hash_func(key) % self.capacity
        idx = hash_idx
        probe = 0
        first_tombstone = -1
        while True:
            node = self.hash_table[idx]
            if node is None:
                target = first_tombstone if first_tombstone != -1 else idx
                self._insert_at(target, Node(key, value))
                return
            if node is DEAD:
                if first_tombstone == -1:
                    first_tombstone = idx
            elif node.key == key:
                node.data = value
                return
            probe += 1
            if probe >= self.capacity:
                # table appears full (shouldn't happen when used correctly)
                raise Exception("hash table is full during _insert_no_resize")
            idx = self._probing_func(hash_idx, probe)

    def insert(self, key, value):
        """Public insert: resize if needed, then insert without resizing."""
        # trigger resize if insertion would exceed load factor
        if self.size + 1 > int(self.capacity * self.load_factor):
            self._expand_and_reallocate()

        # safe insertion that doesn't trigger nested resizes
        try:
            self._insert_no_resize(key, value)
        except Exception:
            # on unexpected full table, expand and retry
            self._expand_and_reallocate()
            self._insert_no_resize(key, value)

    def _expand_and_reallocate(self):
        """Double capacity and reinsert live entries without nested resizes."""
        old_table = self.hash_table
        old_count = self.size

        self.capacity = self.capacity * 2
        self.hash_table = [None for _ in range(self.capacity)]
        self.size = 0

        for e in old_table:
            if e is not None and e is not DEAD:
                self._insert_no_resize(e.key, e.data)

        assert self.size == old_count

    def search(self, key, to_return_idx=False):
        hash_idx = self._hash_func(key)
        idx = hash_idx
        prob_term = 1
        idx_set = set()
        while 1:
            idx_set.add(idx)
            node = self.hash_table[idx]
            if node is None:
                raise KeyError(key)
            elif node is not DeadNode:
                if node.key == key:
                    return node.data if not to_return_idx else idx
            idx = self._probing_func(hash_idx, prob_term)
            prob_term += 1
            if idx in idx_set:
                if len(idx_set) == self.size:
                    raise KeyError(key)
                else:
                    raise Exception("hash table issue: chaos of cycles")

    def remove(self, key):
        idx = self.search(key, to_return_idx=True)
        self.hash_table[idx] = DeadNode

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
    ht = LinearProbingHashTable(5)

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
