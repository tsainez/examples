with open("PythonSummary.txt", "r") as file:
    search = input("Enter word to search for: ")
    count = 0
    for word in file.read().split(' '):
        if search.lower() in word.lower():
            count += 1
    print(count)
