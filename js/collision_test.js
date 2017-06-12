// Include the pyrin library.
const pyrin = require("./pyrin");

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
let a = pyrin("a");

console.log("Trying to find:\n  ", a);

for (let i = 2; ; i++) {
    // Get a string.
    let word = convertToNumberingScheme(i);

    // Get the hash of the incremented string.
    let hash = pyrin(word);

    // Does it match the hash of 'a'?
    if (hash == a) {
        console.log('Attempts:', i, word);
    }
}
