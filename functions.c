#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


// ------------------ First ------------------ //


// function that converts a float to a binary string
char* float_to_binary(float value) {
  unsigned char*  x= (unsigned char*)&value;// Convert the float value to a pointer to an unsigned char array
  char* binary = (char*)malloc(sizeof(char) * (sizeof(float) * 8 + 1));// Allocate memory for the binary string (1 byte per bit, plus a null terminator)
  if (!binary) {// Error: failed to allocate memory for binary string
    return NULL;
  }
  memset(binary, '0', sizeof(float) * 8);// Initialize the binary string with 0s
  binary[sizeof(float) * 8] = '\0';

  
  for (int i = sizeof(float) - 1; i >= 0; i--) {// Iterate over the bytes of the float value, starting with the most significant byte
    for (int j = 7; j >= 0; j--) {// Iterate over the bits of the current byte, starting with the most significant bit
      if (x[i] & (1 << j)) {// Extract the j-th bit of the i-th byte and set the corresponding bit in the binary string
        binary[(sizeof(float) - i - 1) * 8 + (7 - j)] = '1';
      }
    }
  }

  return binary;
}


// function that switches the significand and exponent positions in string representation of float
char* switch_significand_exponent_string(char* value) {
  size_t len = strlen(value);
  char* switched = (char*)malloc(len + 1);

  int exponent_start = 1;
  int exponent_end = 8;

  strncpy(switched, value, 1);// Copies the sign bit to the beginning of the switched string
  strncpy(switched + 1, value + exponent_end + 1, len - exponent_end - 1);// Copies the significand to the middle of the switched string
  strncpy(switched + len - exponent_end, value + exponent_start, exponent_end - exponent_start + 1);// Copies the exponent to the end of the switched string

  
  switched[len] = '\0';// Adds null terminator to the end of the switched string

  return switched;
}


// expand the significand to 52 bits and the exponent to 11 bits
char* expand_switched_significand_exponent(char* switched_value) {
    char sign_bit = switched_value[0];
    char* significand_bits = switched_value + 1;
    char* exponent_bits = switched_value + 9;
    
    // Converts exponent to decimal and apply bias
    int exponent_decimal = strtol(exponent_bits, NULL, 2) - 127 + 1023;

    // Converts expanded exponent back to binary string
    char* exponent_binary = float_to_binary((float)exponent_decimal);
    char exponent_bits_new[12];
    strncpy(exponent_bits_new, exponent_binary + 8, 12);
    exponent_bits_new[11] = '\0';

    // fills significand with zeros to get 52 bits
    char significand_bits_new[53];
    strncpy(significand_bits_new, significand_bits, 23);
    memset(significand_bits_new + 23, '0', 29);
    
    // Concatenates the new sign, significand, and exponent into a single binary string
    char* expanded_value = malloc(65);
    snprintf(expanded_value, 65, "%c%s%s", sign_bit, significand_bits_new, exponent_bits_new);
    
    return expanded_value;
}



// ------------------ Second ------------------ //
//print the value of a variable in binary
void print_binary(unsigned int  value) {
    int num_bits = sizeof(unsigned int) * 8;// Calculates the number of bits in an unsigned int
   
    for (int i = num_bits - 1; i >= 0; i--) { // Prints the bits from left to right
        printf("%d", (value >> i) & 1);
    }
    
}
// This function takes a float value and returns its binary representation as an unsigned int
unsigned int float_to_uint(float value) {
    unsigned int result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

// function tnahat extracts the significand from float using bit operations
  unsigned int get_significand(float value) {
   unsigned int u = *((unsigned int*)&value);  // Casts the float to an unsigned int pointer, and then dereference it to get the value as an unsigned int
    unsigned int m = 0x7FFFFF; // Masks the unsigned int with 0x7FFFFF to keep only the significand bits
    return u & m;// Returns the masked unsigned int, which contains the significand bits of the input float
}

// function that extracts the exponent from float using bit operations
unsigned int get_exponent(float value) {
   unsigned int u = *((unsigned int*)&value); // Casts the float to an unsigned int pointer, and then dereference it to get the value as an unsigned int
    unsigned int m = 0x7F800000; // Masks the unsigned int with 0x7F800000 to keep only the exponent bits
    unsigned int e = (u & m); // Extracts the exponent bits 
    return e;
}

// function that extracts the sign from float using bit operations
unsigned int get_sign(float value) {
unsigned int u = *((unsigned int*)&value);// Converts the float to an unsigned int
unsigned int m = 0x80000000; //a mask for the sign
unsigned int s = (u & m); // Extracts the sign bits 
    return s;
}

// function that switches the significand and exponent positions in float using bit operations using previous functions
unsigned int switch_significand_exponent(float value) {
unsigned int u = *((unsigned int*)&value);// Converts the float to an unsigned int
    unsigned int sign = u & 0x80000000;// Extracts the sign bit by masking with 0x80000000
    unsigned int exponent = (u & 0x7F800000);// Extracts the exponent by masking with 0x7F800000
    unsigned int significand = u & 0x007FFFFF;// Extracts the significand by masking with 0x007FFFFF
    return sign | (significand << 8) | (exponent >> 23);// Combine the sign, exponent, and significand using the bitwise OR operator

}




