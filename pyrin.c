#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyrin.h>

static uint64_t random_number;
static char *seed_next;
char *all_chars = "0123456789abcdef";

/**
 * A simple ceiling function.
 * @param x The number to get the ceiling of.
 * @return The next largest integer after x.
 */
int ceil(float x) {
    int num = (int)x;

    if(num == x) {
        return num;
    }

    return num + 1;
}

/**
 * Initializes the a random number generator.
 * @param seed The seed to start off the PRNG.
 */
void ps_rand(char *seed) {
    seed_next = seed;
}

/**
 * Creates a random number.
 * @param seed The seed to start off the PRNG.
 * @return The random number.
 */
uint64_t p_rand() {
    // Get the micro hash (aka the random number) of the seed.
    random_number = micro_hash(seed_next);

    // Turn the random number into a hexadecimal string.
    seed_next = ltostr(random_number, 16);

    // Return the random number.
    return random_number;
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

/**
 * Creates a temporary hash of a string.
 *
 * @param input The input string.
 * @return The hash value as an unsigned long integer.
 */
uint64_t micro_hash(char *input) {
    // Get the length of the input string.
    int len = strlen(input);

    // Initialize the hash value to 0.
    uint64_t hash = 0;

    // Return 0 if a 0 length string was passed.
    if (!len) {
        return hash;
    }

    // Repeat the following process for each character in the string.
    for (int i = 0; i < len; i++) {
        // Get the character.
        uint8_t c = input[i];

        // Shift the hash by 5 positions left and subtract the current
        // hash from the result of the shift, and adds the character to
        // the new hash.
        hash = ((hash << 5) - hash) + c;

        // Avoid having negative values by converting it into a 31-bit
        // integer.
        hash = hash & 0x7fffffff;
    }

    // Return the actual hash.
    return hash;
}

/**
 * Creates a temporary hash of a string.
 *
 * @param input The input string.
 * @return The hash.
 */
uint8_t *pyrin(char *input) {
    // Get the length of the input string.
    int len = strlen(input);

    // Initialize the PRNG.
    ps_rand(input);

    uint8_t part_a[64];
    uint8_t *result = malloc(64 * sizeof(char));

    // Generate a random string.
    for (int i = 0; i < 64; i++) {
        part_a[i] = p_rand() % 55291;
    }

    if (len <= 64) {
        // Fill up the string to make it into an even 64 bytes.
        for (int i = 0; i < 64; i++) {
            if (i < len) {
                result[i] = part_a[i] ^ input[i];
            }
            else {
                result[i] = part_a[i] ^ (p_rand() % 55291);
            }
        }
    }
    else {
        // Get the amount of parts.
        int parts = ceil((double)len / 64);

        for(int i = 0; i < parts; i++) {
            char *block = malloc(64 * sizeof(char) + 1);
            int block_length = 64;

            if(i == parts - 1) {
                block_length = len - (i * 64);
            }

            // Get the block and save it in the block variable.
            strncpy(block, input + (i * 64), block_length);

            // Get the block's hash.
            block = pyrin(block);

            // XOR the block's hash with the result.
            for (int j = 0; j < 64; j++) {
                result[j] = part_a[j] ^ block[j];
            }
        }
    }

    return result;
}
