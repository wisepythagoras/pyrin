#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pyrin.h>
#include <strops.h>

char *convertToNumberingScheme(int number) {
    uint8_t baseChar = 'a';
    char *letters = (char *)malloc(sizeof(char));
    int i = 0;

    do {
        number -= 1;
        letters = (char *)realloc(letters, (i + 1) * sizeof(char));
        letters[i++] = baseChar + (number % 26);
        number = (number / 26) >> 0;
    } while(number > 0);

    return letters;
}

int main(int argc, char **argv) {
    // A single letter.
    char *result = pyrin("a");
    printf("%s\n", to_hex(result));

    // An empty string.
    result = pyrin("");
    char *zero_length = result;
    printf("%s\n", to_hex(result));

    // A short string.
    result = pyrin("This is my string");
    printf("%s\n", to_hex(result));

    // Another short string.
    result = pyrin("conmarap");
    printf("%s\n", to_hex(result));

    // Same string as above with only one character difference.
    result = pyrin("Conmarap");
    printf("%s\n", to_hex(result));

    // Large input.
    result = pyrin("Lorem ipsum dolor sit amet, nunc leo consectetuer elit velit, id sapien, egestas consectetuer purus in, vel ipsum curabitur lorem amet. Enim non massa, a nulla et cras erat egestas. Tellus nec ipsum maecenas placerat, in curae lacinia. A donec. Duis ut dolor turpis eget suspendisse, lacus diam ante aliquam dolor posuere, dolor sed lacinia consequat augue condimentum, sollicitudin wisi tristique lectus vel. Pellentesque commodo. Non dui tellus nunc sed aliquam. Amet turpis tincidunt sapien vel duis. Tellus vel nam ipsum pulvinar, etiam pede tellus nam donec, mollis elementum. Sapien ac, per nec non magna risus, sed at donec sit fusce. Sed hendrerit vestibulum sed venenatis torquent, sed tellus scelerisque aliquam. Ut vel lectus, sed quis non sit justo, vitae quisque, non placerat metus, donec sed sagittis velit magna.");
    printf("%s\n", to_hex(result));

    // Same input as above only without a period at the end.
    result = pyrin("Lorem ipsum dolor sit amet, nunc leo consectetuer elit velit, id sapien, egestas consectetuer purus in, vel ipsum curabitur lorem amet. Enim non massa, a nulla et cras erat egestas. Tellus nec ipsum maecenas placerat, in curae lacinia. A donec. Duis ut dolor turpis eget suspendisse, lacus diam ante aliquam dolor posuere, dolor sed lacinia consequat augue condimentum, sollicitudin wisi tristique lectus vel. Pellentesque commodo. Non dui tellus nunc sed aliquam. Amet turpis tincidunt sapien vel duis. Tellus vel nam ipsum pulvinar, etiam pede tellus nam donec, mollis elementum. Sapien ac, per nec non magna risus, sed at donec sit fusce. Sed hendrerit vestibulum sed venenatis torquent, sed tellus scelerisque aliquam. Ut vel lectus, sed quis non sit justo, vitae quisque, non placerat metus, donec sed sagittis velit magna");
    printf("%s\n", to_hex(result));

    /*#define LIMIT 2000000000
    int percentage = 0;

    for(int i = 0; i < LIMIT; i++) {
        char *str = convertToNumberingScheme(i);
        char *hash = pyrin(str);
        
        if (strcmp(hash, zero_length) == 0) {
            printf("%i itterations %s :\n  %s\n", i, str, hash);
            break;
        }

        if ((int)(((float)i / LIMIT) * 100) > percentage) {
            percentage++;

            printf("%i\%\n", percentage);
        }
    }*/
}
