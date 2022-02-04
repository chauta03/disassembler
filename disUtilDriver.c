/*
 * Test Driver to test verifyMIPSInstruction and binToDec.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains characters
 *      representing a valid MIPS instruction, the program calls
 *      binToDec for various segments of the instruction to test the
 *      binToDec function.
 *
 * Usage:
 *          name [ filename ] [ 0|1 ]
 *      where "name" is the name of the executable, "filename" is an
 *      optional file containing the input to read, and " 0" or
 *      "1" specifies that debugging should be turned off or on,
 *      respectively, regardless of any calls to debug_on, debug_off,
 *      or debug_restore in the program.  Both arguments are optional;
 *      if both are present they may appear in either order.  If no
 *      filename is provided, the program reads its input from stdin.
 *      If no debugging choice is provided, the program prints debugging
 *      messages, or not, depending on indications in the code.
 *
 * Input:
 *      The program reads its input from a file passed in as a parameter
 *      on the command line, or reads from the standard input.
 *      Valid input consists of lines of 32 characters representing
 *      binary digits (characters '0' and '1').  Since this is a test
 *      driver, the input should contain both valid input (which is used to
 *      test binToDec) and invalid input to test verifyMIPSInstruction.
 *      To fully test verifyMIPSInstruction, the invalid input should
 *      include tests for the following cases:
 *          - a line that contains fewer than 32 characters
            - a line that contains more than 32 characters
            - a line with nothing
            - a line with 1 at the beginning and characters
 *          - a line that contains invalid characters (other than '0' and '1')
 *      To fully test binToDec, the file should contain valid input with:
 *          - a string with 1's in positions 6..10 to test all 1's
 *          - a string with an character in the beginning
 *          - a string with an character at the end
 *
 * Output:
 *      For each line of valid input, this program prints (or should print)
 *      a series of decimal numbers representing tests of the binToDec
 *      function.  For each invalid line, the program prints an error
 *      message to stderr saying so.  (The program also prints an error
 *      message if it cannot open the file.)
 *
 * Author:  Chau Ta
 *
 * Creation Date:  Jan 15th, 2022
 *        modified: Modification_Date        reason
 *        modified: Modification_Date        reason
 *
 */

/* include files go here */
#include "disassembler.h"

int main (int argc, char *argv[])
{
    FILE * fptr;               /* file pointer */
    char   buffer[BUFSIZ];     /* place to store line that is read in */
    int    length;             /* length of line read in */
    int    lineNum = 0;        /* keep track of input line numbers */

    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    /* Provide warning if user did not specify input file on command line. */
    if ( fptr == stdin )
    {
        printf("%s%s%s%s", "Warning: No input file provided, ",
                "so the program is now expecting you\nto provide the input ",
                "from the keyboard or from redirected stdin.\n",
                "Type control-D to end input from keyboard.\n");
    }

    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain an ASCII version of a valid MIPS machine
     * language instruction, represented as 32 character '0's and '1's
     * followed by a newline, rather an actual 32-bit binary MIPS
     * machine language instruction.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        lineNum++;

        /* If the last character in the string is a newline, "remove" it
         * by replacing it with a null byte. (On Windows, the newline might
         * be preceded by a separate carriage return.)
         */
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[--length] = '\0';      /* remove; pre-decrement length */
        if (buffer[length - 1] == '\r')
            buffer[--length] = '\0';      /* remove; pre-decrement length */

        /* If debugging is turned on, echo the input line. */
        printDebug ("\nLine %d: %s\n", lineNum, buffer);

        /* Verify that the string contains 32 '0' and '1' characters.
         * If the string is valid, call testBinToDec to do various tests to
         * ensure that binToDec works correctly.
         * If the string is invalid, verifyMIPSinstruction should print
         * an informative error message.
         */
        if ( verifyMIPSInstruction(lineNum, buffer) )
        {
            printDebug("\tVerified to be valid MIPS instruction.\n");
        }

    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
