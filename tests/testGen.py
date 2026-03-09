import numpy as np
import random
import os

def randomMatrix(n, minVal = -100, maxVal = 100):
    return np.random.randint(minVal, maxVal + 1, size = (n, n))

# This method uses LU-decomposition
def getSpecificMatrix(size, det):
    L = np.eye(size, dtype=int)
    U = np.zeros((size, size), dtype=int)

    if abs(det) < 1e-8:
        for i in range(size):
            for j in range(i, size):
                U[i, j] = random.randint(-100, 100)

        U[0, 0] = 0
        for i in range(size):
            for j in range(i):
                L[i, j] = random.randint(-100, 100)
        return L @ U
        
    diagElements = []
    remaining = det
    for i in range(size - 1):
        factorRange = min(100, int(abs(remaining)**0.5) + 1)
        candidates = [x for x in range(-factorRange, factorRange + 1) 
                      if x != 0 and remaining % x == 0]
        factor = random.choice(candidates)
        diagElements.append(factor)
        remaining //= factor

    diagElements.append(remaining)

    for i in range(size):
        U[i, i] = diagElements[i]

    for i in range(size):
        for j in range(i + 1, size):
            U[i, j] = random.randint(-25, 25)

    for i in range(size):
        for j in range(i):
            L[i, j] = random.randint(-25, 25)

    A = L @ U

    return A

def generate_tests():
    tests = [
        (2, 0),
        (3, 1),
        (4, -1),
        (5, 42),
        (6, -123),
        (7, 1000),
        (8, -999),
        (9, 12345),
        (10, 0),
        (3, 7)
    ]

    os.makedirs("e2e",       exist_ok = True)
    os.makedirs("e2e/keys",  exist_ok = True)
    os.makedirs("e2e/tests", exist_ok = True)

    for idx, (size, det) in enumerate(tests, start = 1):
        A = getSpecificMatrix(size, det)

        test_file = f"e2e/tests/{idx}.txt"
        ans_file = f"e2e/keys/{idx}.txt"

        with open(test_file, 'w') as f:
            f.write(f"{size}\n")
            flat = A.flatten()
            f.write(' '.join(map(str, flat)))

        with open(ans_file, 'w') as f:
            f.write(str(det))

if __name__ == "__main__":
    generate_tests()