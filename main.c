#include <stdio.h>
#include "functions.c"
#include <math.h>

int main() {
    float test = 203.5;
    char* bin = float_to_binary(test);
    printf("\n\n\n// ------------------ first Exercise ------------------ //\n\n\n");
    printf("Original value: %f\n", test);
    if (bin) {
        printf("Original value in binary representation as a string: %s\n",bin);//    print the value in binary
  } else {
    printf("Error: failed to allocate memory for binary string\n");
  }

//    switch the significand and exponent in string representation and print the switched value
char* swi=switch_significand_exponent_string(bin);
printf("The switched representation: %s\n",swi);
//    expand the switched string to 64 bits and print the expanded value
char* expanded_value = expand_switched_significand_exponent(swi);
    printf("Expanded value: %s\n", expanded_value);



printf("\n\n\n// ------------------ Second Exercise ------------------ //\n\n\n");

// print the value in binary using the helper function
unsigned int re = float_to_uint(test);
printf("The binary representation of original: ");
print_binary(re);
printf("\n");
//only significand
   unsigned int significand = get_significand(test);
    printf("The significand: ");
    print_binary(significand);
    printf("\n");
    printf("The integer: %u\n", significand);
//only exponent
unsigned int exponent = get_exponent(test);
    printf("The exponent: ");
    print_binary(exponent);
    printf("\n");
//only sign
unsigned int sign = get_sign(test);
    printf("The sign: ");
    print_binary(sign);
    printf("\n");
//switched in bit manipulation
unsigned int sw = switch_significand_exponent(test);
    printf("The switched binary: ");
    print_binary(sw);
    printf("\nThe switched float: %.6f\n", *((float*)&sw));
    return 0;
}

