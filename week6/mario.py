from cs50 import get_int


while True:
    # Gets user input
    height = get_int("Height: ")
    # Checks for correct input
    if height > 0 and height < 9:
        # Prints the structure
        for i in range(height):
            for j in range(height-(i+1)):
                print(" ", end="")
            for j in range(i+1):
                print("#", end="")
            print(" ", end=" ")
            for j in range(i):
                print("#", end="")
            print("#")
        break 
