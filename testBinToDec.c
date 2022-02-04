/*
 * testBinToDec
 *
 * Calls binToDec in a variety of ways to thoroughly test that function.
 *
 * void testBinToDec(char bitString[])
 *   @param  bitString the string containing characters representing bits
 *   Pre-condition: bitString contains 32 characters representing binary
 *		    digits ('0' and '1') followed by a null byte
 *
 * If called with debugging turned on, this function prints a series of
 * decimal numbers representing the results of calling binToDec in a
 * variety of ways.  For example,
 *      - a string of invalid length
 *      - a string of "normal length" from the middle of the input line
 *      - a string of length 1
 *      - a string of length 32
 *      - a string with invalid begin/end
 *
 * Author:  Chau Ta
 *
 * Creation Date:  Jan 15th, 2022
 *	modified: Jan 31st, 2022    Include test cases
 *
 */

/* include files go here */
#include "disassembler.h"

void testBinToDec(char bitString[])
{
    int decimal;

    /* Start with a simple, "normal" call to binToDec that calculates
     * the integer represented by the 5 "bits" in bitString[6] - bitString[10].
     */
    decimal = binToDec(bitString, 6, 10);
    printf("\tbits 6..10: %.5s = %u (decimal)\n", &bitString[6], decimal);
        /* (The %.5s prints a 5-character substring.  The %u prints the
         * result of the call to binToDec as an unsigned decimal integer.)
         *     NOTE: binToDec will print a duplicate of this output if
         *           debugging is turned on.
         */

    /* Test other test cases, including various boundary cases. */

    /* Test case 1: try different length of substrings (valid cases)*/
    int decimal1;
    int decimal2;
    int decimal3;
    int decimal9;
    int decimalT1;
    int decimalT2;

    /* [0] to [5] */
    decimal1 = binToDec(bitString, 0, 5);
    printf("\tbits 0..5: %.6s = %u (decimal1)\n", &bitString[0], decimal1);

    /* [3] to [27] */
    decimal2 = binToDec(bitString, 3, 27);
    printf("\tbits 3..27: %.25s = %u (decimal2)\n", &bitString[3], decimal2);

    /* [15] to [32] */
    decimal3 = binToDec(bitString, 15, 31);
    printf("\tbits 15..31: %.17s = %u (decimal3)\n", &bitString[15], decimal3);

    /* [1] to [1] */
    decimal9 = binToDec(bitString, 1, 1);
    printf("\tbits 1..1: %.1s = %u (decimal4)\n", &bitString[1], decimal9);

    /* [0] to [30] */
    decimalT1 = binToDec(bitString, 0, 30);
    printf("\tbits 0..30: %.31s = %u (decimalT1)\n", &bitString[0], decimalT1);

    /* [0] to [31] */
    decimalT2 = binToDec(bitString, 0, 31);
    printf("\tbits 0..31: %.32s = %u (decimalT2)\n", &bitString[0], decimalT2);

    /* Test case 2: try different length of substrings (invalid cases) */
    int decimal4;
    int decimal5;
    int decimal6;

    decimal4 = binToDec(bitString, 0, 34); /* [0] to [34] which is out of bound */

    decimal5 = binToDec(bitString, 5, 2); /* [5] to [2] */

    decimal6 = binToDec(bitString, -1, 2); /* [-1] to [2] which is out of bound */
}
