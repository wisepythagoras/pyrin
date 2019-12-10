const pyrin = require("./pyrin");

let str = "";

if (process.argv.length > 2) {
    str = process.argv[process.argv.length - 1];
}

// A single letter.
var result = pyrin(str);
console.log(pyrin.toHex(result));