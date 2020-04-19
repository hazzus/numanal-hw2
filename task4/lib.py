import numpy as np

EPS = 1e-9

def eps_eq(a, b):
    return abs(a - b) < EPS

def eps_root(a, b, x):
    return eps_eq(np.linalg.norm(np.matmul(a, x) - b), 0)

def solve(a, b, w, iterations=100, initial=None):
    n = len(a)
    if initial == None:
        initial = np.zeros(n)

    x = initial
    i_no = 0
    while not eps_root(a, b, x) and i_no < iterations:
        i_no += 1
        for i in range(n):
            sigma = np.dot(a[i], x) - a[i][i] * x[i]
            x[i] = (1 - w) * x[i] + w/a[i][i] * (b[i] - sigma)

    return x

if __name__ == "__main__":
    n = int(input())
    matrix = [list(map(float, input().split())) for _ in range(n)]
    free = list(map(float, input().split()))
    print(solve(matrix, free, 1.5))
