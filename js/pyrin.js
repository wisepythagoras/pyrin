/**
 * The JavaScript implementation of my cryptographic hash function.
 */

/**
 * Get the pyrin hash of a string.
 * @param {String} input The string to hash.
 */
function pyrin(input) {
    // Instanciate the PRNG.
    let rand = new PRand(input);
    let part_a = [];
    let result = [];

    // Generate 64 bytes of random character codes.
    for (let i = 0; i < 64; i++) {
        part_a.push(rand.rand() % 255);
    }

    if (input.length <= 64) {
        // Fill up the string to make it into an even 64 bytes.
        for (let i = 0; i < 64; i++) {
            let charCode;

            if (i < input.length) {
                charCode = part_a[i] ^ input.charCodeAt(i);
                result.push(charCode);
            } else {
                charCode = part_a[i] ^ (rand.rand() % 255);
                result.push(charCode);
            }

            result[i] = ((result[i] & rand.rand() % 255) ^ rand.rand() % 255);
        }

        let rounds = (rand.rand() % 90 + 10);

        // Shuffle and obfuscate the output.
        for (let i = 0; i < rounds; i++) {
            result = shuffle_and_obfuscate(result, rand);
        }

        return result;
    } else {
        // Get the amount of parts.
        let parts = Math.ceil(input.length / 64);

        for (let i = 0; i < parts; i++) {
            // Get the block and save it in the block variable.
            let block = input.substring(i * 64, (i + 1) * 64);

            // Get the block's hash.
            block = pyrin(block);

            // XOR the block's hash with the result.
            for (let j = 0; j < 64; j++) {
                result[j] = part_a[j] ^ block[j];
            }

            result[i] = ((result[i] & rand.rand() % 255) ^ rand.rand() % 255);
        }
    }

    let rounds = (rand.rand() % 90 + 10);

    // Shuffle and obfuscate the output.
    for (let i = 0; i < rounds; i++) {
        result = shuffle_and_obfuscate(result, rand);
    }

    rand = undefined;

    // Return the string.
    return result;
}

/**
 * Convert the int array into a array of hex values.
 * @param {Array} str The int array to convert.
 */
function toHex(str) {
    let rand = new PRand();

    // Convert the hash's int values to hex.
    for (let i = 0; i < str.length; i++) {
        str[i] = rand.ltostr(str[i]);

        if (str[i].length == 1) {
            str[i] = "0" + str[i];
        }
    }

    return str.join('');
}

/**
 * Shuffle and obfuscate an array of characters.
 * @param {Uint8Array} arr The array with the chars.
 * @param {PRand} rand The PRNG.
 * @returns {Uint8Array}
 */
function shuffle_and_obfuscate(arr, rand) {
    for (let i = 0; i < 64; i++) {
        let j = rand.rand() % 64;
        let randNum = rand.rand() % 256;

        let temp = arr[j];
        arr[j] ^= (randNum & arr[i]);
        arr[i] ^= (randNum & arr[j]);
    }

    return arr;
}

class PRand {
    /**
     * The pseudo-random number generator based on the DJB2 function.
     * @param {String} seed
     */
    constructor(seed) {
        this.seed = seed;
        this.all_chars = "0123456789abcdef";
    }

    /**
     * Generate a random number.
     * @return {int}
     */
    rand() {
        // Get the hash of the seed.
        let number = this.m_djb_hash(this.seed);

        // Create the next seed.
        this.seed = this.ltostr(number);

        // Return the number.
        return number;
    }

    /**
     * Converts a number into a hex string.
     * @param {int} number The number to convert.
     * @return {String}
     */
    ltostr(number) {
        if (number < 0) {
            number = 0xFFFFFFFF + number + 1;
        }

        return number.toString(16);
    }

    /**
     * The DJB2 function, remastered.
     * here: http://www.cse.yorku.ca/~oz/hash.html
     * @param {String} input The string to hash.
     * @return {int}
     */
    m_djb_hash(input) {
        // Get the length of the input string.
        let len = input.length;

        // Initialize the hash value to 5381.
        let hash = 5381;

        // Return 0 if a 0 length string was passed.
        if (!len) {
            return hash;
        }

        // Repeat the following process for each character in the string.
        for (let i = 0; i < len; i++) {
            // Get the character.
            let c = input.charCodeAt(i);

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
}

if (typeof module != "undefined") {
    module.exports = pyrin;
    module.exports.toHex = toHex;
    module.exports.PRand = PRand;
}