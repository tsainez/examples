#
#  sumAll.asm
#  
#
#  Created by Anthony Sainez on 3/30/20.
#

.data

enter: .asciiz "Enter integer (0 to end): "
positivePrompt: .asciiz "The sum of the positive integers is: "
negativePrompt: .asciiz "\nThe sum of the negative integers is: "


.text

li $s0, 0 # pos
li $s1, 0 # neg

loop:
    li $v0, 4 # load immediate
    la $a0, enter # prompt
    syscall

    li $v0, 5
    syscall # input
    move $t0, $v0
    beqz $t0, done # branch on greater than or equal to zero
    bltz $t0, negativeAdd # if x > 0
    add $s0, $s0, $t0 # is pos
    j skip

negativeAdd:
    add $s1, $s1, $t0

skip:
    j loop

done:
    li $v0, 4
    la $a0, positivePrompt # prompt
    syscall

    move $a0, $s0
    li $v0, 1
    syscall # print it!

    li $v0, 4
    la $a0, negativePrompt # prompt
    syscall

    move $a0, $s1
    li $v0, 1
    syscall # print it!
