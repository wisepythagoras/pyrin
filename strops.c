#include <strops.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *all_chars = "0123456789abcdef";

/**
 * Reverses a string.
 * @param string The string to inverse.
 */
void reverse(char *string) {
    int length, c;
    char *begin, *end, temp;
 
    length = strlen(string);
    begin = string;
    end = string;
 
    for (c = 0; c < length - 1; c++) {
        end++;
    }
 
    for (c = 0; c < length / 2; c++) {
        temp = *end;
        *end = *begin;
        *begin = temp;
 
        begin++;
        end--;
    }
}

/**
 * Reverse a uint8_t array of length len.
 * @param char* str The string to reverse.
 * @param int len The length of the string.
 */
void reverse_alt(uint8_t *str, int len) {
    int i;

    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

/**
 * Returns a number in a different base, between 2 and 16.
 *
 * @param val The input decimal number.
 * @param unsigned The base to convert to.
 * @return The encoded integer.
 */
char *ltostr(uint64_t val, unsigned base) {
    if (base > 16 || base < 2) {
        return "";
    }

    // Initialize the string with a length of 0.
    char *result = (char *)malloc(sizeof(char));
    int i = 0;

    // Convert the integer to a string of whatever base
    // by looking into the above hex_chars string for the
    // given character to represent each portion.
    do {
        // Reallocate space to the end string so that we
        // can make it larger.
        result = (char *)realloc(result, (i + 1) * sizeof(char));

        // Then find out with character to append to the
        // string.
        result[i++] = all_chars[val % base];
    } while((uint64_t)(val /= base) > 0);

    // Reverse the string.
    reverse(result);

    // Terminate the stirng.
    result[i] = '\0';

    // Return the result.
    return result;
}

/**
 * Converts a string to a hex.
 *
 * @param input The input buffer.
 * @return The hexadecimal value.
 */
uint8_t *to_hex(uint8_t *input) {
    uint8_t *buffer = malloc(128 * sizeof(char) + 1);

    for (int i = 0, j = 0; i < 64; i++, j += 2) {
        char *hex = dechex(input[i], NULL, 0, 1);
        // printf("%i: %s\n", input[i], hex);
        buffer[j] = hex[0];
        buffer[j + 1] = hex[1];
    }

    return buffer;
}

/**
 * Convert a single decimal into a hexadecimal value.
 *
 * @param dec The decimal value.
 * @param hex The string to put it back into.
 * @param len The length of the string.
 * @param int Ensure that the string starts at the correct address.
 * @return The hexadecimal value.
 */
char* dechex(unsigned dec, char *hex, int len, int fill) {
    if (hex == NULL) {
        len = dec & 0xFFFF0000 ? (dec & 0xFF000000 ? (dec & 0xF0000000 ? 8 : 7) : (dec & 0x00F00000 ? 6 : 5)) : (dec & 0x0000FF00 ? (dec & 0x0000F000 ? 4 : 3) : (dec & 0x000000FF ? (dec & 0x000000F0 ? 2 : 2) : 2));
        hex = malloc((len + 1) * sizeof(char));
    }
    
    char *hex2 = hex + len, *end = hex2;
    *hex2 = '\0';
    
    for (--hex2; ; hex2--) {
        *hex2 = all_chars[dec & 0xF];

        if(dec < 16) {
            *(--hex2) = '0';
        }

        dec >>= 4;

        if (dec == 0) {
            break;
        }
    }
    
    // Make the string start at the correct address.
    if (fill) {
        if (hex2 > hex) {
            char *c = hex, *s = hex2;
            for (c, s; s < end; s++) {
                *(c++) = *s;
            }
            
            // Fill with zeros at end.
            for (c; c < end; c++) {
                *(c++) = '\0';
            }
        }
        
        return hex;
    }
    
    return hex2;
}
