#
#  recursion.asm
#
#
#  Created by Anthony Sainez on 4/17/20.
#
#
# #include<stdio.h>
#
# int recursion(int m){
#     if(m == 10)
#         return 2;
#     else if(m == 11)
#         return 1;
#     else
#         return recursion(m + 2) + m + recursion(m + 1);
# }
#
# int main(){
#     int x;
#     printf("Please enter an integer: ");
#     scanf("%d", &x);
#     printf("%d\n", recursion(x));
#     return 0;
# }

.data
    str1: .asciiz "Please enter an integer: "
.text

main:
    addi $sp, $sp, -4
    li $v0, 4           # prompt for input
    la $a0, str1
    syscall

    li $v0, 5
    syscall             # value entered by user stored in $v0
    move $a0, $v0
    addi $v0, $zero, 0  # clear v0 for return

    jal recursion       # recursion

    sw $v0, 0($sp)      # prints final ra
    lw $a0, 0($sp)

    li $v0, 1
    syscall

    j finish               # totally finished


recursion:
    addi $sp, $sp, -12  # push stack frame
    sw $ra, 8($sp)      # storing return address in stack frame

    # m = 10?
    addi $t0, $zero, 10
    bne $t0, $a0, ten

    addi $v0, $v0, 2
    j end

ten:
    addi $t0, $zero, 11 # m = 11?
    bne $t0, $a0, eleven

    addi $v0, $v0, 1

    j end

eleven:
    sw $a0, 4($sp)
    addi $a0, $a0, 2    # m + 2

    jal recursion       # recursion
    lw $a0, 4($sp)      # first ra

    addi $a0, $a0, 1    # m + 1
    jal recursion       # recursion

    lw $a0, 4($sp)      # loads first return value
    add $v0, $v0, $a0   # add all values together
    j end

end:
    lw $ra, 8($sp)      # get val for return
    addi $sp, $sp, 12   # pop stack frame
    jr $ra

finish:
    addi $sp, $sp 4     # pop stack frame
    li $v0, 10
    syscall

