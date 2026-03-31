# Python time hashing demo

import hashlib
import time
import sys
from datetime import timedelta

# Calculando hash() de várias coisas...

MAX = 10000000

print(f"Executando {MAX} vezes cada função de hash\n")

print("Função hash()\n")
start_time = time.monotonic()

for val in range(MAX):
    x = hash(val)
    #if val < 20:
    #    print(x)

end_time = time.monotonic()

print(timedelta(seconds=end_time - start_time))

# Hashes seguros (criptográficos)

print("\nHashes seguros:\n")

print("Algoritmos: ",hashlib.algorithms_available)
print()

start_time = time.monotonic()
for val in range(MAX):
    x = hashlib.sha256(bytearray(str(val), 'utf-8'))
end_time = time.monotonic()
print("SHA-256:",timedelta(seconds=end_time - start_time))

start_time = time.monotonic()
for val in range(MAX):
    x = hashlib.sha512(bytearray(str(val), 'utf-8'))
end_time = time.monotonic()
print("SHA-512:",timedelta(seconds=end_time - start_time))

h = hashlib.new('ripemd160')
start_time = time.monotonic()
for val in range(MAX):
    x = h.update(bytearray(str(val), 'utf-8'))
end_time = time.monotonic()
print("RIPEMD-160:",timedelta(seconds=end_time - start_time))

h = hashlib.new('blake2b')
start_time = time.monotonic()
for val in range(MAX):
    x = h.update(bytearray(str(val), 'utf-8'))
end_time = time.monotonic()
print("BLAKE2B:",timedelta(seconds=end_time - start_time))

h = hashlib.new('shake_256')
start_time = time.monotonic()
for val in range(MAX):
    x = h.update(bytearray(str(val), 'utf-8'))
end_time = time.monotonic()
print("SHAKE256:",timedelta(seconds=end_time - start_time))

