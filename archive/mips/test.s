# Compute the sum of N integers: 1 + 2 + 3 + ... + N
# In this case, N = 5.

main:
    # Initialize registers
    addiu   $t0, $0, 5        # initialize number of integers to be 5
    addiu    $t1, $0, 0        # initialize counter (i)
    addiu    $t2, $0 0        # initialize sum

    # Main loop body
loop:
    addiu    $t1, $t1, 1    # i = i + 1
    addu    $t2, $t2, $t1    # sum = sum + i
    beq    $t0, $t1, exit    # if i = N, continue
    j    loop

    # Exit routine - sum stored in t2
exit:
    addiu    $v0, $0, 10        # exit
    syscall     # should exit since unsupported

