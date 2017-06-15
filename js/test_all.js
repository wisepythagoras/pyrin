const pyrin = require("./pyrin");

// A single letter.
var result = pyrin("a");
console.log(pyrin.toHex(result));

// An empty string.
result = pyrin("");
var zero_length = result;
console.log(pyrin.toHex(result));

// A short string.
result = pyrin("This is my string");
console.log(pyrin.toHex(result));

// Another short string.
result = pyrin("conmarap");
console.log(pyrin.toHex(result));

// Same string as above with only one character difference.
result = pyrin("Conmarap");
console.log(pyrin.toHex(result));

// Large input.
result = pyrin("Lorem ipsum dolor sit amet, nunc leo consectetuer elit velit, id sapien, egestas consectetuer purus in, vel ipsum curabitur lorem amet. Enim non massa, a nulla et cras erat egestas. Tellus nec ipsum maecenas placerat, in curae lacinia. A donec. Duis ut dolor turpis eget suspendisse, lacus diam ante aliquam dolor posuere, dolor sed lacinia consequat augue condimentum, sollicitudin wisi tristique lectus vel. Pellentesque commodo. Non dui tellus nunc sed aliquam. Amet turpis tincidunt sapien vel duis. Tellus vel nam ipsum pulvinar, etiam pede tellus nam donec, mollis elementum. Sapien ac, per nec non magna risus, sed at donec sit fusce. Sed hendrerit vestibulum sed venenatis torquent, sed tellus scelerisque aliquam. Ut vel lectus, sed quis non sit justo, vitae quisque, non placerat metus, donec sed sagittis velit magna.");
console.log(pyrin.toHex(result));

// Same input as above only without a period at the end.
result = pyrin("Lorem ipsum dolor sit amet, nunc leo consectetuer elit velit, id sapien, egestas consectetuer purus in, vel ipsum curabitur lorem amet. Enim non massa, a nulla et cras erat egestas. Tellus nec ipsum maecenas placerat, in curae lacinia. A donec. Duis ut dolor turpis eget suspendisse, lacus diam ante aliquam dolor posuere, dolor sed lacinia consequat augue condimentum, sollicitudin wisi tristique lectus vel. Pellentesque commodo. Non dui tellus nunc sed aliquam. Amet turpis tincidunt sapien vel duis. Tellus vel nam ipsum pulvinar, etiam pede tellus nam donec, mollis elementum. Sapien ac, per nec non magna risus, sed at donec sit fusce. Sed hendrerit vestibulum sed venenatis torquent, sed tellus scelerisque aliquam. Ut vel lectus, sed quis non sit justo, vitae quisque, non placerat metus, donec sed sagittis velit magna");
console.log(pyrin.toHex(result));