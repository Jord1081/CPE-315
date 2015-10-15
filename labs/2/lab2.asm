.text
.globl main

main:	      la $a0, prompt	# Prompt user to enter input
            li $v0, 4
            syscall

            li $v0, 5	         # Read user input
            syscall

            move $a0, $v0	      # Convert input to hexadecimal
            la $a1, hex
            #jal bintohex

            move $a0, $a1	      # Print hexadecimal string
            li $v0, 4
            syscall

            la $a0, la_prompt    # Inform user we are adding numbers in table
            li $v0, 4
            syscall

            la, $a0, loop_table  # Get address of loop_table
            jal loop_add         # Add values in loop_table
            move $a0, $v0
            li $v0, 1
            syscall              # Print result
            la $a0, newline
            li $v0, 4
            syscall              # Print newline


            li $v0, 10	         # Exit program
            syscall


bintohex:   li $t0, 0




fibonacci:  



double_add: 

loop_add:   addi $sp, $sp, -4
            sw $ra, 0($sp)    # Store return address on stack

            li $v0, 0         # Initialize $v0 to 0
            li $t0, 9         # Initialize counter to 9

add_loop:   lw $t1, 0($a0)      # Get value at address in $a0
            add $v0, $v0, $t1 # Sum $v0 and next value from table
            add $a0, $a0, 4   # Increment address in $a0
            addi $t0, $t0, -1 # Decrement counter
            bne $t0, $zero, add_loop

            lw $ra, 0($sp)    # Get return address
            addi $sp, $sp, 4
            jr $ra

.data

prompt:	   .asciiz "Enter a integer\n"


newline:    .byte 0x0A, 0x00
la_prompt:  .asciiz "Adding table of numbers\n"
test1:	   .word 15
hex:	      .space 10
loop_table: .word 4155543, 3112 , -2, 1054, -33543, 1233, -433433, 10101, 16384
