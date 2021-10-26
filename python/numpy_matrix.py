import numpy as np

print("-------------------- Part A --------------------")
x = np.arange(2, 10).reshape(4, 2)
print(x)

print("-------------------- Part B --------------------")
x = np.tile(np.array([[0, 1], [1, 0]]), (4, 4))
print(x)

print("-------------------- Part C --------------------")
List = np.unique(np.array([10, 20, 10, 30, 20, 40, 20, 20, 10, 30, 0, 50, 10]))
print(List)

print("-------------------- Part D --------------------")
List = np.array([6, 75, 9, 82, 36, 42, 59, 3, 52, 1,
                32, 68, 93, 4, 27, 85, 0, -3, 57])
List = List[List > 37]
print(List)

print("-------------------- Part E --------------------")
# Convert the values of a list of values in Centigrade into Fahrenheit degrees
List = np.array([0, 12, 45.21, 34, 99.91])
List = (List * 9/5) + 32
print(List)
