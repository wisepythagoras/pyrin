// Include the libraries that we need.
const cluster = require("cluster");
const term = require("terminal-kit").terminal;
const numeral = require("numeral");
const numCPUs = require("os").cpus().length;
const pyrin = require("./pyrin");
const toHex = pyrin.toHex;
const hrstart = process.hrtime();

let i = 0;
let difficulty = 7;
let nonce = 0;
let contents = "amazing!!!";
let computations_per_second = 0;
let seconds = 0;

/**
 * Returns the next nonce.
 * @returns {int}
 */
function getNextNonce() {
    let ret = nonce;
    nonce++;
    return ret;
}

/**
 * Adds another computation for this second.
 */
function addComputation() {
    computations_per_second++;
}

const int = setInterval(() => {
    term.eraseLine();
    term.backwardTab(2);
    term(numeral(computations_per_second).format("0.000a"));
    computations_per_second = 0;
    seconds++;
}, 1000);

// https://www.sitepoint.com/how-to-create-a-node-js-cluster-for-speeding-up-your-apps/
// if (cluster.isMaster) {
//     for (let i = 0; i < numCPUs; i++) {
//         cluster.fork();
//     }
//
//     cluster.on("exit", (worker, code, signal) => {
//         console.log(`Worker ${worker.process.pid} died`);
//     });
// } else {
/**
 * Compute the hash corresponding to an int.
 */
function computeNextHash() {
    // Get the nonce.
    let nonce = getNextNonce();

    // Get the hash of the incremented string.
    let hash = toHex(pyrin(contents + nonce));

    // Does it match the hash of 'a'?
    if (hash.substring(0, difficulty) === Array(difficulty + 1).join('0')) {
        clearInterval(int);

        term("\nAttempts: %d, nonce: %d\n", i, nonce);
        term("Hash: %s\n", hash);

        let hrend = process.hrtime(hrstart);
        term("Execution time: %dms - %ds\n", hrend[1] / 1000000, seconds);

        return;
    }

    i++;

    addComputation();

    // Wait for the next tick and re-run the function.
    setImmediate(computeNextHash);
}

// Start computing hashes to try and match the hash of 'a'.
computeNextHash();

// console.log(`Worker ${process.pid} started`);
// }