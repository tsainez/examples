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
        
        #addi $sp, $sp -4    # Feel free to change the increment if you need for space.
        #sw $ra, 0($sp)
        # Implement your main here

        la  $a0, str0       # load address of str0 for syscall
        li  $v0, 4          # print string service
        syscall             # "Welcome to BobCat Candy, home to the famous BobCat Bars!"
        
        la $a0, price       # load address of price prompt for syscall
        #li $v0, 4          # print string service, but $v0 is already 4
        syscall             # "\nPlease enter the price of a BobCat Bar:\n"

        addi $sp, $sp, -4
        li  $v0, 5          # read integer service
        syscall             # allow user input for price of BobCat Bar
        move    $a0, $v0    # store user input in $a0
        sw  $a0, 0($sp)     # store price in the stack

        la  $a0, wrappers   # load address of wrappers prompt for syscall
        li  $v0, 4          # print string service
        syscall             # "\nPlease enter the number of wrappers needed to exchange for a new bar:\n"
        
        li  $v0, 5          # read integer service
        syscall             # allow user input for number of wrappers
        move    $a1, $v0    # store user input in $a1
                            # no need to use the stack pointer for this.

        la  $a0, money      # load address of money prompt for syscall
        li  $v0, 4          # print string service
        syscall             # "How, how much do you have?\n"

        li  $v0, 5          # read integer service
        syscall             # allow user input for money available
        move    $s0, $v0    # store user input in $s0
                            # it is important we save this value for its use later

        la  $a0, good       # load address of the "good" bit
        li  $v0, 4          # print string service
        syscall             # "Good! let me run the number..."

        # Now, the price is stored in at 0($sp),
        # and the number of wrappers for exchange is in $a1,
        # and the money available to spend is in $s0.

        lw $a0, 0($sp)
        
        # Before we calculate how many in total you can buy...
        # we should check to see you can buy any in the first place
        
        div $t0, $s0, $a0
        li $v0, 0
        beq $t0, $zero, none

        li $v0, 4,
        la $a0, firstbuy
        syscall

        add $a0, $t0, $zero # print this number
        li $v0, 1
        syscall

        li $v0, 4
        la $a0, bars
        syscall

        # save amount of bars initially bought, $a0
        # save amount of wrappers needed, $a1
        move $a0, $t0
        move $t2, $t0

        jal maxBars     # Call maxBars to calculate the maximum number of BobCat Bars

        # Print out final statement here
        add $v0, $v0, $t2

        none:   # Case if insufficent money to buy a single bar
        sw $v0, 0($sp)

        li $v0, 4
        la $a0, with
        syscall

        add $a0, $s0, $zero
        li $v0, 1
        syscall

        li $v0, 4
        la $a0, max
        syscall

        lw $v0, 0($sp)
        add $a0, $v0, $zero
        li $v0, 1
        syscall

        li $v0, 4
        la $a0, exclamation
        syscall

        j end   # Jump to the end of the program!
        
maxBars:
        # This function calculates the maximum number of BobCat Bars.
        # It takes in 3 arguments ($a0, $a1, $a2) as n, price, and money. It returns the maximum number of bars
        addi $sp, $sp, -12
        sw $ra 8($sp)
        div $t0, $a0, $a1
        bne $t0, $zero, newBars
        li $v0, 0
        
        # Time to end
        lw $ra, 8($sp)
        addi $sp, $sp, 12
        jr $ra

        #//div $s2, $s0    # total = totalmoney / bar
        #//mflo $s3
        
        #//div $s2, $s0
        #//mflo $s3

        #//beq $s3, $0, end

        #//li  $v0, 4
        #//la  $a0, firstbuy
        #//syscall

        #//li $v0, 1
        #//move $a0, $s3
        #//syscall

        #//li $v0, 4
        #//la $a0, bars
        #//syscall

        #//add $s6, $s6, $s3 # counter = counter + total
        #//jal newBars

        #//jr $ra
        
        # div $t2, $t0
        # mflo    $s1
        # mfhi    $s2
        
        # ble $s1, 1, end

        # You're about to see why we saved those arguments to $s0-s2!

        # la  $a0, firstbuy   # load address of first buy prompt
        # li  $v0, 4          # print string service
        # syscall             # "\nYou first buy "

        # li  $v0, 1          # print integer service
        # move    $a0, $s1
        # syscall             # print out amount of bars bought first time

        # move    $t3, $s1

        # la  $a0, bars       # adding bars to the end of that number
        # li  $v0, 4          # print string service
        # syscall

		# jal newBars 	# Call a helper function to keep track of the number of bars.
		
		# jr $ra
		# End of maxBars

newBars:
        div $a0, $a0, $a1
        sw $a0, 4($sp)
        
        #//beq $s3, $0 end
        #//div $s3, $s1
        #//mflo $s4
        
        #//beq $s4, $0, end
        
        li $v0, 4
        la $a0, another
        syscall
        
        lw $a0 4($sp)
        li $v0, 1
        syscall

        #//move $a0, $s4
        #//move $s3, $s4
        #//syscall

        li $v0, 4
        la $a0, bars
        syscall

        # This is the recursion bit...
        lw $a0 4($sp)
        jal maxBars

        # Now we've returned...
        lw $a0 4($sp)
        add $v0, $a0, $v0   # update the return value
        
        # Jump to the end
        lw $ra, 8($sp)
        addi $sp, $sp, 12
        jr $ra

#newBars:
		# This function calculates the number of BobCat Bars a user will receive based on n.
		# It takes in 2 arguments ($a0, $a1) as number of wrappers left so far and n.
        # div     $s1, $t1
        # mflo    $s1
        # mfhi    $s4

        # ble     $s1, 0, end
		
		# la  $a0, another    # load address of the "another" bit
        # li  $v0, 4          # print string service
		# syscall             # "\nThen, you will get another "
		
        # li  $v0, 1          # print integer service
        # move    $a0, $s1
        # syscall             # print the amount of extra bars

        # la  $a0, bars       # add bars to the end of the number
        # li  $v0, 4          # print string service
        # syscall             # "____ bars"
        
        # add $t3, $t3, $s1
        # add $s1, $s1, $s4
                          
        # j newBars # recurse

		#jr $ra
		# End of newBars

end:
        #//la $t1, ($s2)
        #//la $t2, ($s6)
        #la  $a0, with   # load address of "with" bit
        #li  $v0, 4      # print string service
        #syscall         # "\nWith $"

        #li  $v0, 1      # print integer service
        #move $a0, $t2   # $t2 = $a2 = money
        #syscall         # print out money we had

        #la  $a0, max    # load address of "max" statement
        #li  $v0, 4      # print string service
        #syscall

        #li  $v0, 1      # print integer service
        #move $a0, $t3
        #syscall

        #la  $a0, exclamation    # load address of the exclamation
        #li  $v0, 4              # print string service
        #syscall

        #//li $v0, 4
        #//la $a0, with
        #//syscall

        #//li $v0, 1
        #//move $a0, $s2
        #//syscall

        #//li $v0, 4
        #//la $a0, max
        #//syscall

        #//li $v0, 1
        #//move $a0, $s6
        #//syscall

        #//li $v0, 4
        #//la $a0, exclamation
        #//syscall

	# Terminating the program
	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10
	syscall
