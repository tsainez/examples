#
#  BobCatCandy.s
#
#
#  Created by Anthony Sainez on 5/1/20.
#  Collaborated with Aaron Norstrom.
#

.data
str0: .asciiz "Welcome to BobCat Candy, home to the famous BobCat Bars!"
# Declare any necessary data here
price:		.asciiz "\nPlease enter the price of a BobCat Bar:\n"
wrappers:	.asciiz "Please enter the number of wrappers needed to exchange for a new bar:\n"
money:		.asciiz "How much do you have?\n"
good:		.asciiz "Good! Let me run the numbers..."
firstbuy:	.asciiz "\nYou first buy "
bars:		.asciiz " bars."
another:	.asciiz "\nThen, you will get another "
with:		.asciiz "\nWith $"
max:		.asciiz ", you will receive a maximum of "
exclamation:	.asciiz " Bobcat Bars!"

.text

main:
	#This is the main program.
	#It first asks user to enter the price of each BobCat Bar.
	#It then asks user to enter the number of bar wrappers needed to exchange for a new bar.
	#It then asks user to enter how much money he/she has.
	#It then calls maxBars function to perform calculation of the maximum BobCat Bars the user will receive based on the information entered.
	#It then prints out a statement about the maximum BobCat Bars the user will receive.
	
	# Implement your main here
	
	la	$a0,	str0	# load address of str0 for syscall
	li	$v0,	4	# print string service
	syscall			# "Welcome to BobCat Candy, home to the famous BobCat Bars!"
	
	la	$a0,	price	# load address of price prompt for syscall
	#li	$v0,	4	# print string service, but $v0 is already 4
	syscall			# "\nPlease enter the price of a BobCat Bar:\n"
	
	addi	$sp,	$sp,	-4
	li	$v0,	5	# read integer service
	syscall			# allow user input for price of BobCat Bar
	move	$a0,	$v0	# store user input in $a0
	sw	$a0,	0($sp)	# store price in the stack
	
	la	$a0,	wrappers	# load address of wrappers prompt for syscall
	li	$v0,	4		# print string service
	syscall				# "\nPlease enter the number of wrappers needed to exchange for a new bar:\n"
        
	li	$v0,	5 	# read integer service
	syscall			# allow user input for number of wrappers
	move	$a1,	$v0	# store user input in $a1
				# no need to use the stack pointer for this.
	
	la	$a0,	money	# load address of money prompt for syscall
	li	$v0,	4	# print string service
	syscall			# "How, how much do you have?\n"
	
	li	$v0,	5	# read integer service
	syscall			# allow user input for money available
	move	$s0,	$v0	# store user input in $s0
				# it is important we save this value for its use later

	la	$a0,	good	# load address of the "good" bit
	li	$v0,	4	# print string service
	syscall			# "Good! let me run the number..."

	# Now, the price is stored in at 0($sp),
	# and the number of wrappers for exchange is in $a1,
	# and the money available to spend is in $s0.

	lw	$a0,	0($sp)
        
	# Before we calculate how many in total you can buy...
	# we should check to see you can buy any in the first place
        
	div	$t0,	$s0,	$a0
	li	$v0,	0
	beq	$t0,	$zero,	none	# If we don't have enough money to buy even one, 
        				# We can just skip straight to the end of main.

	li	$v0,	4,
	la	$a0,	firstbuy
	syscall
	
	add	$a0,	$t0,	$zero	# print this number
	li	$v0,	1
	syscall
	
	li	$v0,	4
	la	$a0,	bars
	syscall
	
	move	$a0,	$t0
	move	$t2,	$t0
	
	jal	maxBars	# Call maxBars to calculate the maximum number of BobCat Bars
	
	# Print out final statement here
	add	$v0,	$v0,	$t2
	
	none:	# Case if insufficent money to buy a single bar
		# This is still inside of main.
        	
	sw	$v0,	0($sp)

	li	$v0,	4
	la	$a0,	with
	syscall
	
	add	$a0,	$s0,	$zero
	li	$v0,	1
	syscall
	
	li	$v0,	4
	la	$a0,	max
	syscall			# append the "max" statement
	
	lw	$v0,	0($sp)
	add	$a0,	$v0,	$zero
	li	$v0,	1
	syscall
	
	li	$v0,	4
	la	$a0,	exclamation
	syscall
	
	j	end	# Jump to the end of the program!
        
maxBars:
	# This function calculates the maximum number of BobCat Bars.
	# It takes in 3 arguments ($a0, $a1, $a2) as n, price, and money. It returns the maximum number of bars
	addi	$sp,	$sp,	-12
	sw	$ra,	8($sp)
        
	div	$t0,	$a0,	$a1
        
	bne	$t0,	$zero,	newBars
        
	li	$v0,	0	# Reset this, so the assembler doesn't get confused.
        			# If you don't reset this, it will add 4 to the max.
        
	# Restore return address
	lw	$ra,	8($sp)
	addi	$sp,	$sp,	12
	jr	$ra

newBars:
	div	$a0,	$a0,	$a1
	sw	$a0,	4($sp)
	
	li	$v0,	4
	la	$a0,	another
	syscall		# prints out "You will get another..."
        
	lw	$a0,	4($sp)
	li	$v0,	1
	syscall		# prints out how many more we got on this round
	
	li	$v0,	4
	la	$a0,	bars
	syscall		# append "bars" to the end of the amount.
	
	# This bit is really important.
	lw	$a0,	4($sp)
	jal	maxBars
	
	# Now we've returned...
	lw	$a0,	4($sp)
	add	$v0,	$a0,	$v0	# Update return value
	
	# Jump to the end
	lw	$ra,	8($sp)
	addi	$sp,	$sp,	12
	jr	$ra
	
end:
	# Terminating the program
	lw	$ra,	0($sp)
	addi	$sp,	$sp,	4
	li	$v0,	10
	syscall
