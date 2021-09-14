# adder.py
# Anthony Sainez

while True:
    try:
        nums = input("Enter numbers: ")
        total = 0
        if(len(nums.split(' ')) > 1):
            for num in nums.split(' '):
                total += float(num)
        print(total)
        break
    except ValueError:
        print("Error: incorrect input. Please try again.")
        continue
