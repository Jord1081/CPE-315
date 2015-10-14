.text
.globl main

main:	la $a0, prompt	# Prompt user to enter input
	li $v0, 4
	syscall

	li $v0, 5	# Read user input
	syscall

	move $a0, $v0	# Convert input to hexadecimal
	la $a1, hex
	jal bintohex

	move $a0, $a1	# Print hexadecimal string
	li $v0, 4
	syscall

	li $v0, 10	# Exit program
	syscall


bintohex:
	li $t0, 0

hexloop:
	



fibonacci: 



double_add: 



.data

prompt:	.asciiz "Enter a integer\n"
test1:	.word 15
hex:	.space 10
