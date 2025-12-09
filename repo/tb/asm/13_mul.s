.text
.globl main

main:
    # Test 1: MUL (normal 32 bit result)
    # 10 * -5 = -50
    li a1, 10
    li a2, -5
    mul a3, a1, a2      

    # Test 2: MULH (signed * signed, high 32 bits)
    # 0x7FFFFFFF * 0x7FFFFFFF = 0x3FFFFFFF
    # 0x3FFFFFFF = 1,073,741,823
    li a1, 0x7FFFFFFF
    li a2, 0x7FFFFFFF
    mulh a4, a1, a2     

    # Test 3: MULHU (unsigned * unsigned, high 32 bits)
    # 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE
    # 0xFFFFFFFE = -2
    li a1, -1           # 0xFFFFFFFF
    li a2, -1
    mulhu a5, a1, a2    

    # Test 4: MULHSU (signed * unsigned, high 32 bits)
    # 0x80000000 * 2 = 0xFFFFFFFF
    # 0xFFFFFFFF = -1
    li a1, 0x80000000
    li a2, 2
    mulhsu a6, a1, a2

    # Checksum: Sum all results into a0
    # a0 = a3 + a4 + a5 + a6
    # a0 = (-50) + (1,073,741,823) + (-2) + (-1)
    # a0 = 1,073,741,770
    add a0, a3, a4
    add a0, a0, a5
    add a0, a0, a6

done:
    j done
