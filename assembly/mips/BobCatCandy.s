#
#  BobCatCandy.s
#
#
#  Created by Anthony Sainez on 5/1/20.
#

.data
str0: .asciiz "Welcome to BobCat Candy, home to the famous BobCat Bars!"
# Declare any necessary data here

price:          .asciiz "\nPlease enter the price of a BobCat Bar:\n"
wrappers:       .asciiz "Please enter the number of wrappers needed to exchange for a new bar:\n"
money:          .asciiz "How much do you have?\n"
good:           .asciiz "Good! Let me run the numbers..."
firstbuy:       .asciiz "\nYou first buy "
bars:           .asciiz " bars."
another:        .asciiz "\nThen, you will get another "
with:           .asciiz "\nWith $"
max:            .asciiz ", you will receive a maximum of "
exclamation:    .asciiz " Bobcat Bars!"

.text

main:
        #This is the main program.
        #It first asks user to enter the price of each BobCat Bar.
        #It then asks user to enter the number of bar wrappers needed to exchange for a new bar.
        #It then asks user to enter how much money he/she has.
        #It then calls maxBars function to perform calculation of the maximum BobCat Bars the user will receive based on the information entered.
        #It then prints out a statement about the maximum BobCat Bars the user will receive.
        
        addi $sp, $sp -4    # Feel free to change the increment if you need for space.
        sw $ra, 0($sp)
        # Implement your main here
        la  $a0, str0       # load address of str0 for syscall
        li  $v0, 4          # print string service
        syscall             # "Welcome to BobCat Candy, home to the famous BobCat Bars!"
        
        la $a0, price       # load address of price prompt for syscall
        #li $v0, 4          # print string service, but $v0 is already 4
        syscall             # "\nPlease enter the price of a BobCat Bar:\n"

        li  $v0, 5          # read integer service
        syscall             # allow user input for price of BobCat Bar
        move    $t0, $v0    # store user input in $t0

        la  $a0, wrappers   # load address of wrappers prompt for syscall
        li  $v0, 4          # print string service
        syscall             # "\nPlease enter the number of wrappers needed to exchange for a new bar:\n"
        
        li  $v0, 5          # read integer service
        syscall             # allow user input for number of wrappers
        move    $t1, $v0    # store user input in $t1

        la  $a0, money      # load address of money prompt for syscall
        li  $v0, 4          # print string service
        syscall             # "How, how much do you have?\n"

        li  $v0, 5          # read integer service
        syscall             # allow user input for money available
        move    $t2, $v0    # store user input in $t2

        la  $a0, good       # load address of the "good" bit
        li  $v0, 4          # print string service
        syscall             # "Good! let me run the number..."

        # Now, the price is stored in $t0,
        # and the number of wrappers for exchange is in $t1,
        # and the money available to spend is in $t2.

        move    $a0,    $t1
        move    $a1,    $t0
        move    $a2,    $t2

        # save the arguments to later, they are special

        move    $s0,    $a0 # n
        move    $s1,    $a1 # price
        move    $s2,    $a2 # money

        jal maxBars     # Call maxBars to calculate the maximum number of BobCat Bars

        # Print out final statement here

        j end            # Jump to end of program

maxBars:
        # This function calculates the maximum number of BobCat Bars.
        # It takes in 3 arguments ($a0, $a1, $a2) as n, price, and money. It returns the maximum number of bars
        div $t2, $t0
        mflo    $s1
        mfhi    $s2
        
        ble $s1, 1, end

        # You're about to see why we saved those arguments to $s0-s2!

        la  $a0, firstbuy   # load address of first buy prompt
        li  $v0, 4          # print string service
        syscall             # "\nYou first buy "

        li  $v0, 1          # print integer service
        move    $a0, $s1
        syscall             # print out amount of bars bought first time

        move    $t3, $s1

        la  $a0, bars       # adding bars to the end of that number
        li  $v0, 4          # print string service
        syscall

		jal newBars 	# Call a helper function to keep track of the number of bars.
		
		jr $ra
		# End of maxBars

newBars:
		# This function calculates the number of BobCat Bars a user will receive based on n.
		# It takes in 2 arguments ($a0, $a1) as number of wrappers left so far and n.
        div     $s1, $t1
        mflo    $s1
        mfhi    $s4

        ble     $s1, 0, end
		
		la  $a0, another    # load address of the "another" bit
        li  $v0, 4          # print string service
		syscall             # "\nThen, you will get another "
		
        li  $v0, 1          # print integer service
        move    $a0, $s1
        syscall             # print the amount of extra bars

        la  $a0, bars       # add bars to the end of the number
        li  $v0, 4          # print string service
        syscall             # "____ bars"
        
        add $t3, $t3, $s1
        add $s1, $s1, $s4
                          
        j newBars # recurse

		jr $ra
		# End of newBars

end:
        la  $a0, with   # load address of "with" bit
        li  $v0, 4      # print string service
        syscall         # "\nWith $"

        li  $v0, 1      # print integer service
        move $a0, $t2   # $t2 = $a2 = money
        syscall         # print out money we had

        la  $a0, max    # load address of "max" statement
        li  $v0, 4      # print string service
        syscall

        li  $v0, 1      # print integer service
        move $a0, $t3
        syscall

        la  $a0, exclamation    # load address of the exclamation
        li  $v0, 4              # print string service
        syscall

		# Terminating the program
		lw $ra, 0($sp)
		addi $sp, $sp 4
		li $v0, 10
		syscall
