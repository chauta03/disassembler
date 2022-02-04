# A simple makefile

GCC=gcc -Wall -Wextra -Wpedantic -Wformat -Wshadow -Wredundant-decls \
    -Wstrict-prototypes
# Can also use -Wtraditional or -Wmissing-prototypes

# When you just run `make` without specifying a target, it looks for a
# target called `all`.
#  Switch to the second, alternative version of the "all" target
#  when you're ready to compile the disassembler project.

all:	disassembler
# all:	disUtil disassembler

disUtil:	disassembler.h \
		same.h \
    		printFuncs.h \
    		process_arguments.h \
		process_arguments.c \
    		verifyMIPSInstruction.c \
		binToDec.c \
		testBinToDec.c \
		printDebug.c \
		printError.c \
		same.c \
		disUtilDriver.c
		$(GCC) process_arguments.c printDebug.c printError.c \
		    same.c verifyMIPSInstruction.c binToDec.c \
		    testBinToDec.c disUtilDriver.c -o disUtil

# Alyce will test your utility functions with her own main.
alyce:	disassembler.h \
	same.h \
	printFuncs.h \
	process_arguments.h \
	process_arguments.c \
	verifyMIPSInstruction.c \
	binToDec.c \
	printDebug.c \
	printError.c \
	same.c \
	alyceMain.c
	$(GCC) process_arguments.c verifyMIPSInstruction.c binToDec.c \
	    printDebug.c printError.c same.c alyceMain.c -o alyceDisUtil

# The assembler will probably have other source files in addition to these.
# Be sure to include them in the list of dependencies below and also in the
# $(GCC) compilation command immediately following the dependencies.
disassembler:	disassembler.h \
		same.h \
    		printFuncs.h \
    		process_arguments.h \
		process_arguments.c \
    		verifyMIPSInstruction.c \
		binToDec.c \
		getRegName.c \
		printDebug.c \
		printError.c \
		same.c \
		disassembler.c
		$(GCC) process_arguments.c verifyMIPSInstruction.c binToDec.c \
		    same.c getRegName.c \
		    printDebug.c printError.c disassembler.c -o disassembler

clean: 
	rm -rf *.o disUtil disassembler
