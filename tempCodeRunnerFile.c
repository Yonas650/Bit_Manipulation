

int main() {
    float test = 203.5;
    char* bin = float_to_binary(test);
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
