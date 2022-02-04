/*
 * binToDec
 *
 * Converts the binary digits from string[begin] to string[end] to a
 * decimal integer.
 *
 * int binToDec(char string[], int begin, int end)
 *   @param  string the string containing characters representing bits
 *   @param  begin  the index of the first character to include in the
 *                      calculation
 *   @param  end    the index of the last character to include in the
 *                      calculation
 *   @return  the decimal equivalent of the binary number represented by
 *	      the characters in string[begin] - string[end].
 *   Pre-conditions: begin and end are valid indices in array string;
 *		     begin <= end;
 *		     end - begin <= 32;
 *   		     every character from string[begin] to string[end]
 *		     (including those two) has a character value '0' or '1'
 *
 * For example, assume A is a character array that contains the
 *    following characters:
 *            '1'  '0'  '1'  '1'  '0'  '1'  '0'  '0'  '1'
 *    The call binToDec(A, 2, 5) converts the binary number 1101
 *    (represented by the substring A[2] - A[5]) to the decimal integer
 *    13 and returns it.
 * 
 * Note: The decimal value returned may appear to be negative if the
 * string being converted is long enough (end - begin + 1 == 32)
 * and if the first character is '1'.
 *
 * Implementation:
 *	Describe interesting implementation details here, if any.
 *      This function reads valid input. Valid input consists of lines of 32 characters representing
 *      binary digits (characters '0' and '1'). The function takes part of 
 *      the input from digit 'begin' to digit 'end' and converts binary value
 *      to decimal value.
 *      This function uses pow(base, exp) from math.c to calculate corresponding
 *      decimal value.
 *   
 *
 * Author:  Chau Ta
 *
 * Creation Date:  Jan 15th, 2022
 *	modified: Jan 31st, 2022    Get rid of unnecessary codes
 */

/* include files go here */
#include "disassembler.h"

int binToDec(char string[], int begin, int end)
{
    int decimal = 0;
    
    int length = end - begin + 1;
    int i = end;
    int pow2 = 1;

    int keepTrack; /* integer keepTrack keeps track of how many digits need to go through and the value 2 of each digit */

    for (keepTrack = 0; keepTrack < length; keepTrack++) 
    {
        if (keepTrack != 0)
        {
                pow2 *= 2; /* update pow2 each round */
        }

        if (string[i] == '0') /* If encounter '0', decimal value stays the same. */
        {
        }
        else if (string[i] == '1') /* If encounter '1', add the value of current digit to the decimal value. */
        {
            decimal += pow2; /* accumulate decimal value */
        }
        i--; /* update keepTrack after each loop */       
    } /* end of for loop */

    return decimal;
}
