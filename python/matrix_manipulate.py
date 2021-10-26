import numpy as np
a = np.array([[1, 2, 3, ],
              [4, 5, 6, ],
              [7, 8, 9]])
b = np.array([[3, 1, 4, ],
              [2, 6, 1],
              [2, 9, 7]])

print("-------------------- Part A --------------------")
print(a + b)

print("-------------------- Part B --------------------")
print(np.cross(a, b))

print("-------------------- Part C --------------------")
print(np.linalg.det(a))

print("-------------------- Part D --------------------")
print(np.linalg.inv(b))

print("-------------------- Part E --------------------")
print(np.linalg.eigvals(a))
