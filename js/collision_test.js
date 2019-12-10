const r = new (require("randbytes")).urandom.getInstance();

// Include the pyrin library.
const pyrin = require("./pyrin");
const toHex = pyrin.toHex;

function convertToNumberingScheme(number) {
    let baseChar = 'a';
    let letters = '';
    let i = 0;

    do {
        number -= 1;
        letters += String.fromCharCode(baseChar.charCodeAt(0) + number % 26);
        number = (number / 26) >> 0;
    } while(number > 0);

    return letters;
}

// Get the hash of the letter a.
let a = toHex(pyrin("a"));

console.log("Trying to find:\n  ", a);

var i = 0;

/**
 * Compute the hash corresponding to an int.
 */
function computeNextHash() {
    r.getRandomBytes(1000, bytes => {
        let word = bytes.toString();

        // Get the hash of the incremented string.
        let hash = toHex(pyrin(word));
    
        // Does it match the hash of 'a'?
        if (hash == a) {
            console.log("Attempts:", i, word);
            require("fs").writeFileSync("collision", `${i}:${word}`);
            return;
        }
        else {
            console.log(i, hash);
        }
    
        i++;
    
        // Wait for the next tick and re-run the function.
        setImmediate(computeNextHash);
    });
}

// Start computing hashes to try and match the hash of 'a'.
computeNextHash();
