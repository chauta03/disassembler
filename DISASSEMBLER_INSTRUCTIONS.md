# Disassembler Programming Project

See the
[Disassembler PP assignment](www.cs.kzoo.edu/cs230/Projects/DisassemblerProj.html)
for the instructions for this assignment, coding tips, links to helpful
documents, and submission requirements.

The Disassembler project builds upon the Disassembler Utility functions you
have already written: `verifyMIPSInstruction` and `binToDec`.
It also uses the other header files and utility functions that were
provided to you for that project, such as `same.h`, `printFuncs.h`,
`process_arguments` (`.c` and `.h`), `printDebug.c`, and `printError.c`, etc.

Thus, the first thing to do for this project is to copy contents of your
DisUtils project into this repository, add and commit them in git, and
push that to this repository as a starting point.  (Make sure to first fix
any errors or make other changes that were suggested in the grading
feedback to DisUtils.)  At this point, this repository should essentially
be a working copy of your DisUtil repository, with a new README.md file
and two sample test files.

Once you start working on the Disassembler project itself, note that the
Makefile provided to you for the DisUtil project included rules for
compiling the Disassembler also.  You will want to change the definition of
the `all` target to include both disUtil and disassembler (as suggested in
the comments).  Alternatively, you could change it to just specify
disassembler.

Note also that the Makefile assumes that your disassembler program will
include a file called `disassembler.c` containing a `main` function.  The
`main` function you used to test the utility functions makes a good
template for this, so a good starting point is to copy `disUtilDriver.c`,
calling it `disassembler.c`, and then edit it to start implementing your
Disassembler project.

A good second step, as described in the 
[Disassembler PP
assignment](www.cs.kzoo.edu/cs230/Projects/DisassemblerProj.html), is to
complete the `getRegName` function in `getRegName.c` and test it by adding
code to your `main` function or to `testBinToDec`.

The only new files provided here are a small sample test file and its
associated expected output.  The sample "machine code" test file is titled
`smallSampleTestfile.input`.    You can compare your output to the expected
output in `smallSampleTestfile.output` to check your progress.  Note, though,
that these two files only test some cases; they do not provide a thorough
test suite.

Following agile development principles, repeatedly Edit, Test, and Add/Commit
until the program is done. You can `git push` to Kit as often as you want.
(See the [Working with Git Repositories in
Kit](http://www.cs.kzoo.edu/CSShared/HelpFiles/Kit/RepositoryAssignments.md)
document for more information about writing a program within a Git
repository.)

Don't forget to provide a `README.md` file with external documentation about
your program, as described in the 
[Disassembler PP assignment](www.cs.kzoo.edu/cs230/Projects/DisassemblerProj.html).

When you are ready to submit your work, click on the "Turn In"
button. (You should still be able to push further changes to Kit
after turning an assignment in if you need to.)

