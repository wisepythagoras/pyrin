#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pyrin.h>
#include <strops.h>
#include <time.h>

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
    char *arg = "";

    if (argc > 1) {
        arg = argv[1];
    }

    if (!strcmp(arg, "--benchmark")) {
        clock_t begin = clock();

        for (int i = 0; i < 100000; i++) {
            char *res = (char *) pyrin(convertToNumberingScheme(i));
        }

        // Get the execution time.
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Done after %f seconds!\n", time_spent);
        printf("The speed was %.2f KHs\n", 100000 / time_spent / 1000);
    } else if (!strcmp(arg, "--test")) {
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
    } else {
        char *result = (char *) pyrin(arg);
        printf("%s\n", to_hex((uint8_t *) result));
    }

    return 0;
}
