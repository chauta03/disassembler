/*
 * Disassembler: Takes machine code input and translates to assembly
 *      language equivalent.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains characters
 *      representing a valid MIPS instruction, the program ...
 *        [INCOMPLETE]
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
 *      binary digits (characters '0' and '1'); each line should represent
 *      a valid MIPS instruction or an invalid MIPS instruction for testing
 *      purposes.
 *
 * Output:
 *      For each line of valid input, this program prints ...
 *        [INCOMPLETE]
 *      For each invalid line, the program prints an error
 *      message to stderr saying so.  (The program also prints an error
 *      message if it cannot open the file.)
 *
 * Author:  Chau Ta
 *
 * Creation Date:  1 February, 2022
 *        modified: 1 Feb, 2022 -- implement initial versions of processR
 *                                  and processJ, and a placeholder for
 *                                  processI
 *        modified: 6 Feb, 2022 -- implement the full versions of processR
 *                                  and processJ, and processI
 *
 */

/* include files go here */
#include "disassembler.h"
char * getInstrName(int opcode, char type);

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
            int opcode;
            printDebug("\tVerified to be valid MIPS instruction.\n");
            opcode = binToDec(buffer, 0, 5);
            printDebug("Opcode = %d\n", opcode);

            if ( opcode == 0 )
                processR(buffer, lineNum);
            else if ( opcode == 2 || opcode == 3 )
                processJ(buffer, opcode);
            else
                processI(buffer, opcode, lineNum);
        }

    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}

/* Process R format instructions.
*     @param buffer   character array holding "binary" instruction
*     @param lineNum  line number (for reporting invalid opcodes)
*/
void processR(char buffer[], int lineNum)
{
    int reg1, reg2, reg3, shamt, opcode;
    char * instrName;

    reg2 = binToDec(buffer, 6, 10);
    reg3 = binToDec(buffer, 11, 15);
    reg1 = binToDec(buffer, 16, 20);
    shamt = binToDec(buffer, 21, 25);

    opcode = binToDec(buffer, 26, 31);
    if ( opcode == 0 ) /* sll */
    {
        instrName = "sll";
        printf("%s %s, %s, %d", instrName,
                getRegName(reg1), getRegName(reg3), shamt);
    }
    else if ( opcode == 2 ) /* srl */
    {
        instrName = "srl";
        printf("%s %s, %s, %d", instrName,
                getRegName(reg1), getRegName(reg3), shamt);
    }
    else if ( opcode == 8 ) /* jr */
    {
        instrName = "jr";
        printf("%s %s\n", instrName, getRegName(reg2));
    }
    else
    {
        char type;
        type = 'R';

        instrName = getInstrName(opcode, type);

        if ( instrName == NULL || strcmp( instrName, "invalid" ) == 0 )
            printError("Error on line %d: Invalid funct code %d\n", lineNum, opcode);
        
        printf("%s %s, %s, %s", instrName,
                getRegName(reg1), getRegName(reg2), getRegName(reg3) );
    
    }
}

/* Process J format instructions.
*     @param buffer   character array holding "binary" instruction
*     @param opcode   the opcode for this instruction
*/

void processJ(char buffer[], int opcode)
{
    int address;
    char * instrName;
    if ( opcode == 2 )
        instrName = "j";
    else 
        instrName = "jal";
    address = binToDec(buffer, 6, 31);
    address <<= 2;    /* Multiply address by 4 to restore 00 */
    printf("%s %d\n", instrName, address);
}

/* Process I format instructions.
 *     @param buffer   character array holding "binary" instruction
 *     @param opcode   the opcode for this instruction
 *     @param lineNum  line number (for reporting invalid opcodes)
 */
void processI(char buffer[], int opcode, int lineNum)
{

    /* Get instr name here if you call it for all opcodes; handle error
     * condition if it's an invalid opcode. */
    /* char * instrName = getInstrName(opcode); */

    if ( opcode == 4 || opcode == 5 )  /* beq or bne */
    {
        int reg1, reg2, branchOffset, branchAddress;
        char * instrName;
        if ( opcode == 4 )
            instrName = "beq";
        else
            instrName = "bne";
        reg1 = binToDec(buffer, 6, 10);
        reg2 = binToDec(buffer, 11, 15);
        branchOffset = binToDec(buffer, 16, 31);
        branchAddress = lineNum + branchOffset;
        branchAddress <<= 2;    /* Multiply address by 4 to restore 00 */
        printf("%s %s, %s, %d\n", instrName,
                getRegName(reg1), getRegName(reg2), branchAddress);
    }
    else if ( opcode == 15 )  /*  lui */
    {
        int reg, immediateAddress;
        char * instrName;
        instrName = "lui";
        reg = binToDec(buffer, 11, 15);
        immediateAddress = binToDec(buffer, 16, 31);
        printf("%s %s, %d\n", instrName,
                getRegName(reg), immediateAddress);
    }
    else if ( opcode == 35 || opcode == 43 )  /* lw or sw */
    {
        int reg1, reg2, addressMemory;
        char * instrName;
        if ( opcode == 35 )
            instrName = "lw";
        else
            instrName = "sw";
        reg2 = binToDec(buffer, 6, 10);
        reg1 = binToDec(buffer, 11, 15);
        addressMemory = binToDec(buffer, 16, 31);
        printf("%s %s, %d(%s)\n", instrName, getRegName(reg1),
                 addressMemory, getRegName(reg2) );
    }
    else  /* all the "regular" I-format instructions */
    {
        int sourceReg, destReg, immedAmount;
        /* Handle error condition if it's an invalid opcode. */
        char type;
        type = 'I';

        char * instrName ;
        instrName = getInstrName(opcode, type);

        if ( instrName == NULL || strcmp( instrName, "invalid") == 0 )
            printError("Line %d: Invalid opcode %d\n", lineNum, opcode);
        
        sourceReg = binToDec(buffer, 6, 10);
        destReg = binToDec(buffer, 11, 15);
        immedAmount = binToDec(buffer, 16, 31);
        printf("%s %s, %s, %d\n", instrName, 
                getRegName(destReg), getRegName(sourceReg), immedAmount);
    }
}

/* Process I regular format instructions.
 *     @param opcode   the opcode for this instruction
 *     @return         mnemonic name for given instruction
 */
char * getInstrName(int opcode, char type)
{
    /* Create a static (persistent) array of the mnemonic names,
     *    each of which is a string (char *).
     */
    if ( type == 'I' )
    {
        opcode -= 8; /* Because "regular" I format start from 8 to 13 */
        if ( opcode < 0 || opcode > 5 )
            return "invalid";

        static char * instrArrayI[] =
        {
                "addi","addiu",
                "slti","sltiu",
                "andi","ori"
        };
 
        return instrArrayI[opcode];
    }
    else /* if type is R */
    {
        opcode -= 32; /* Because R instructions start from 32 to 43 without 38, 40 and 41 */
        if ( opcode < 0 || opcode > 11)
            return "invalid";

        static char * instrArrayR[] =
        {
            "add", "addu", "sub", "subu",
            "and", "or", "invalid", "nor",  /* Because R instructions do not include 38 */
            "invalid", "invalid",        /* Because R instructions do not include 40 and 41 */
            "slt", "sltu"
        };
 
        return instrArrayR[opcode];
    }
}

