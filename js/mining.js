// Include the libraries that we need.
const cluster = require("cluster");
const term = require("terminal-kit").terminal;
const numeral = require("numeral");
const pyrin = require("./pyrin");
const toHex = pyrin.toHex;

let i = 0;
let difficulty = 7;
let nonce = 0;
let contents = "amazing!!!";
let computations_per_second = 0;
let seconds = 0;

const int = setInterval(() => {
    term.eraseLine();
    term.backwardTab(2);
    term(numeral(computations_per_second).format("0.000a"));
    computations_per_second = 0;
    seconds++;
}, 1000);

/**
 * Compute the hash corresponding to an int nonce.
 */
function computeNextHash() {
    // Get the hash of the incremented string.
    let hash = toHex(pyrin(contents + nonce));

    // Does the hash match the difficulty with preceeding zeros?
    if (hash.substring(0, difficulty) === Array(difficulty + 1).join('0')) {
        clearInterval(int);

        term("\nAttempts: %d, nonce: %d\n", i, nonce);
        term("Hash: %s\n", hash);
        term("Execution time: %ds\n", seconds);

        return;
    }

    i++;
    nonce++;
    computations_per_second++;

    // Wait for the next tick and re-run the function.
    setImmediate(computeNextHash);
}

// Start computing hashes to try and match the hash of 'a'.
computeNextHash();