// Include the libraries that we need.
const cluster = require("cluster");
const term = require("terminal-kit").terminal;
const numeral = require("numeral");
const numCPUs = require("os").cpus().length;
const pyrin = require("./pyrin");
const toHex = pyrin.toHex;
const hrstart = process.hrtime();

let i = 0;
let difficulty = 6;
let nonce = 0;
let contents = "amazing!!!";
let seconds = 0;
let computations_per_second = 0;

if (cluster.isMaster) {
    const int = setInterval(() => {
        term.eraseLine();
        term.backwardTab(2);
        term(numeral(computations_per_second).format("0.000a"));
        computations_per_second = 0;
        seconds++;
    }, 1000);

    for (let i = 0; i < numCPUs; i++) {
        cluster.fork();
    }

    for (const id in cluster.workers) {
        // Get the worker.
        let worker = cluster.workers[id];

        // Listen for messages.
        (worker => {
            worker.on("message", message => {
                if (message === "getNextNonce") {
                    worker.process.send(nonce++);
                } else if (message === "addComputation") {
                    computations_per_second++;
                } else if (message === "found") {
                    clearInterval(int);

                    for (const wid in cluster.workers) {
                        let otherWorker = cluster.workers[wid];
                        otherWorker.kill();
                    }
                }
            });
        })(worker);
    }

    cluster.on("exit", (worker, code, signal) => {
        // Show some message about the workers?
    });
} else {
    // The only message that the child could receive from the master is
    // one containing the nonce.
    process.on("message", nonce => computeNextHash(nonce));

    /**
     * Send a message to the master.
     * @param {string} command The command to send to the master.
     */
    function send(command) {
        try {
            process.send(command);
        } catch (e) {}
    }

    /**
     * A function to get the next nonce.
     */
    function getNonce() {
        send("getNextNonce");
    }

    /**
     * Compute the hash corresponding to an int nonce.
     */
    function computeNextHash(nonce) {
        // Get the hash of the incremented string.
        let hash = toHex(pyrin(contents + nonce));

        // Does the hash match the difficulty with preceeding zeros?
        if (hash.substring(0, difficulty) === Array(difficulty + 1).join('0')) {
            send("found");

            term("\nAttempts: %d, nonce: %d\n", i, nonce);
            term("Hash: %s\n", hash);

            return;
        }

        i++;

        send("addComputation");

        // Wait for the next tick and re-run the function.
        setImmediate(getNonce);
    }

    getNonce();
}

process.on("exit", () => console.log("Elapsed time", numeral(seconds).format("00:00:00")));