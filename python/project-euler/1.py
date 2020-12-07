#
# Project Euler,
# Problem #1
#
# If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9.
# The sum of these multiples is 23.
# This program can find the sum of all the multiples of 3 or 5 below 1000.

x = 0
for i in range(1000):
    if i % 5 == 0 or i % 3 == 0:
        x += i
        
print(x)
