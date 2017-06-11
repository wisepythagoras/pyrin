#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyrin.h>
#include <strops.h>

static uint64_t random_number;
static char *seed_next;

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
    random_number = m_djb_hash(seed_next);

    // Turn the random number into a hexadecimal string.
    seed_next = ltostr(random_number, 16);

    // Return the random number.
    return random_number;
}

/**
 * Creates a temporary hash of a string.
 *
 * @param input The input string.
 * @return The hash value as an unsigned long integer.
 */
uint64_t m_djb_hash(char *input) {
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
