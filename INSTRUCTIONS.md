#  Disassembler Utility Functions Project

This repository contains the starter code (including a `Makefile` and a
template test file) for a program for which you will write and
test two functions (`verifyMIPSInstruction` and `binToDec`).  These
functions will be useful in the Disassembler program to be written later.

See the
[DisUtils PP assignment](www.cs.kzoo.edu/cs230/Projects/DisUtilitiesProj.html)
for the full instructions for this assignment, coding tips, links to helpful
documents, and submission requirements.  Those instructions do not,
however, assume that you are using a Git repository to get started, so this
document fills in details related to using a Git repository associated with
Kit.

### Compiling and Running Starter Code

You can compile and run the starter code, although it will not produce
valid output until you have written the `verifyMIPSInstruction` and
`binToDec` functions.  To compile the code using the provided Makefile,
just type `make` at a Unix or Linux prompt.

The provided code processes 2 optional command-line arguments, a file name
and a debugging indicator, reads in lines from the file (or standard input,
if no file name is provided), and prints the lines back out to standard
output.  If debugging is turned on, it also prints the length of the line.
To compile the initial provided code, type `make` (or, equivalently,
`make disUtil`).  Look at the code in `disUtilDriver.c` to see what it
does, then try the following tests:
    make           (OR `make disUtil`)
    ./disUtil testfileStarter.txt 0
    ./disUtil testfileStarter.txt 1
    ./disUtil 0 testfileStarter.txt
    ./disUtil 1 testfileStarter.txt
    ./disUtil testfileStarter.txt
If you test it without providing a file name, it will wait for you to type
in the input; you can do this line-by-line, typing Control-D (end-of-file)
when you're done.  For example:
    ./disUtil 1
    Hi there!
    Just testing ...
    Control-D

### Getting Started with the Actual Project

Once you are comfortable with `disUtilDriver.c` you should write and test the
two functions for this assignment: `verifyMIPSInstruction` and `binToDec`.
(Suggestion: implement and test `verifyMIPSInstruction` first.  Add
additional test cases to `testfileStarter.txt` to test it thoroughly.  Once
you have that working, implement `binToDec`, and add appropriate tests to
`testBinToDec`.)

### Looking Ahead to the Disassembler Project

This repository also contains some additional starter code for the
full disassembler program.
(See [here](http://www.cs.kzoo.edu/cs230/Projects/DisassemblerProj.html)
for the project description for the full disassembler program.)
