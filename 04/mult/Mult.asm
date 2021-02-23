// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

//load R0's value to a
@R0
D=M
@a
M=D

//load R1's value to n
@R1
D=M
@n
M=D

//set i to one
@i
M=0

//set sum to zero
@R3
M=0

(LOOP)
    //check if i==n
    @i
    D=M
    @n
    D=D-M
    @END
    D;JEQ

    //add a(R0) to R3
    @a
    D=M
    @R3
    M=D+M

    //add 1 to i(iterate)
    @i
    M=M+1

    //go back to the beggining of the loop
    @LOOP
    0;JMP

(END)
    @END
    0;JMP
