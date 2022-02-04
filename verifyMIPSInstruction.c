/*
 * verifyMIPSInstruction
 *
 * This function verifies that the string provided to it as a paramater
 * contains 32 characters representing binary digits (characters '0' and
 * '1'), followed by a null byte.  If the string contains the wrong
 * number of characters or contains invalid charaters (not '0' or '1'),
 * then the function prints an error message to stderr giving the line
 * number and an appropriate error message.
 *
 * int verifyMIPSInstruction (int lineNum, char instruction[]);
 *      @param lineNum  line number of current instruction (for error messages)
 *      @param instruction string containing what should be machine code
 *                         for a MIPS instruction
 *	Pre-condition:  instruction is a null-terminated string
 *	Post-condition: the string "instruction" has not been modified
 *	Returns: 1 if instruction contained 32 characters representing binary
 *			   digits ('0' and '1') followed by a null byte
 *		 0 if instruction has the wrong number of characters or
 *		           contains invalid characters
 *	Output: Prints an error message to stderr if necessary
 *
 * Author: Chau Ta
 *
 * Creation Date:  Jan 15th, 2022
 *	modified: Jan 31st, 2022	Get rid of unnecessary codes
 *	modified: Modification_Date	reason
 *
 */

/* include files go here */
#include "disassembler.h"

static const int INSTR_LENGTH = 32;

int verifyMIPSInstruction (int lineNum, char instr[])
  /*  returns 1 if instr contains INSTR_LENGTH characters representing binary
   *  digits ('0' and '1'); 0 otherwise
   */
{
    int length;

    length = strlen(instr);
    printDebug ("\tLength: %d\n", length);

    if (length != INSTR_LENGTH)
    {
        printError ("Error: line %d does not have %d chars.\n",
                    lineNum, INSTR_LENGTH);
        return 0;
    }

    /* Check if instr contains only binary digits */
    int i;
    for (i = 0; i < length; i++)
    {
        if (instr[i] != '0' && instr[i] != '1')
        {
            printError ("Error: line %d have invalid digits.\n",
                        lineNum);
            return 0;
        }
    }
    return 1;    
}
