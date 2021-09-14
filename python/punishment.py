with open("CompletedPunishment.txt", "w") as file:
    sentence = input("Enter in a sentence: ")
    repeats = input("Enter in how many times to repeat: ")
    for i in range(int(repeats)):
        file.write(sentence + "\n")
