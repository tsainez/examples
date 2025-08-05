#
#  proc.s
#
#
#  Created by Anthony Sainez on 4/9/20.
#

# include<stdio.h>
#
# int sub(int a, int b){
#     return b - a;
# }
#
# int sum(int m, int n){
#     int p = sub(n+1, m+1);
#     int q = sub(m-1, n-1);
#     return p + q;
# }
#
# int main(){
#     int x=5, y=10;
#     y = y + x + sum(x, y);
#     printf("%d\n", y);
#     return 0;
# }

.data
x: .word 5      # int x = 5
y: .word 10     # int y = 10
p: .word 0      # p and q for funcs
q: .word 0
.text

main:
    la $t0, x		# $s0 = x
	lw $s0, 0($t0)
	la $t0, y		#$s1 = y
	lw $s1, 0($t0)
	add $a0, $a0, $s0
	add $a1, $a1, $s1

	jal sum

	add $s1, $a0, $a1
	add $a0, $s1, $s0

	li $v0, 1		 
	syscall

	j end

sum:
   	 addi $t0, $a1, 1
	addi $t1, $a0, 1

	jal sub
	
	la $t0, p
	lw $s0, 0($t0)
	add $s0, $s0, $v0	# p = sub(n+1, m+1)
	subi $t0, $a0, 1
	subi $t1, $a1, 1
	
	jal sub

	la $t0, q
	lw $s1, 0($t0)
	add $s1, $s1, $v0	# q = sub(m-1, n-1)
	add $s0, $s0, $s1
	addi $ra, $zero, 4194340 # adding to differing return address

	jr $ra
	
sub:	
	sub $v0, $t1, $t0
	jr $ra

end:

