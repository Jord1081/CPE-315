#include <stdio.h>
#include <math.h>

typedef struct {
   int sign;
   int exp;
   long long frac;
} floatNum;

floatNum unpack(float num) {
   floatNum ret;
   unsigned int k = *(unsigned int *)&num; // Trick to get exact bits.

   ret.sign = 0;
   if (k & 0x80000000) // Check and adjust the sign of the number.
      ret.sign = 1;

   // AND the bits with a mask that results in only the rightmost 23 bits
   // selected.
   ret.frac = k & 0x7FFFFF;
   ret.frac |= 0x800000; // Set the 24th bit to 1.

   // Shift |k| 23 bits to the right and then AND with a mask that results
   // in only the 8 right most bits selected.
   ret.exp = (k >> 23) & 0xFF;
   ret.exp -= 127; // Remove bias.

   return ret;
}

float pack(floatNum num) {
   unsigned int ret = 0;

   ret = num.sign << 31; // Shift the sign bit to the most significant bit.

   // Add the bias to the exponent and then shift it 23 bits to the right.
   // Select bits 24 through 31 by ANDing with mask 0x7F8000000 and store in
   // corresponding bits of the return value.
   ret |= ((num.exp + 127) << 23) & 0x7F800000;

   // Select the right most 23 bits by ANDing it with the mask 0x7FFFFF and
   // store in corresponding bits in the return value.
   ret |= (num.frac & 0x7FFFFF);

   return *(float *)&ret; // Trick the compiler to think |ret| is a float.
}

floatNum single_float_add(floatNum lhs, floatNum rhs) {
   floatNum ret;
   ret.sign = 0;

   // Check to see which number is smaller and shift bits and adjust
   // exponent as necessary.
   if (lhs.exp < rhs.exp) {
      lhs.frac >>= rhs.exp - lhs.exp;
      lhs.exp = rhs.exp;
   }
   else if (rhs.exp < lhs.exp) {
      rhs.frac >>= lhs.exp - rhs.exp;
      rhs.exp = lhs.exp;
   }

   // Check the sign of each number and adjust the value of the fraction
   // accordingly.
   if (lhs.sign)
      lhs.frac = -lhs.frac;
   if (rhs.sign)
      rhs.frac = -rhs.frac;

   ret.frac = lhs.frac + rhs.frac;
   ret.exp = lhs.exp;

   // Check for a carry over and adjust bits and exponent if necessary.
   if (ret.frac & 0x100000000) {
      ret.frac >>= 1;
      ret.exp++;
   }

   // Check the sign of the fraction and adjust fraction and sign bit 
   // if necessary.
   if (ret.frac < 0) {
      ret.sign = 1;
      ret.frac = -ret.frac;
   }

   return ret;
}

floatNum single_float_subtract(floatNum lhs, floatNum rhs) {
   // Make the right hand operand the opposite sign.
   if (rhs.sign)
      rhs.sign = 0;
   else
      rhs.sign = 1;

   // Use single_float_add() to compute the difference.
   return single_float_add(lhs, rhs);
}

floatNum single_float_multiply(floatNum lhs, floatNum rhs) {
   floatNum ret;
   // If signs differ, result will be negative so adjust sign accordingly.
   ret.sign = (lhs.sign != rhs.sign);

   ret.frac = lhs.frac * rhs.frac;
   ret.frac >>= 23; // Shift oversized result to correct bit length.

   ret.exp = lhs.exp + rhs.exp; // Add exponents to get correct exponent.
   return ret;
}

void print_unpacked_float(floatNum num) {
   printf("    Sign: 0x%016lX\nExponent: 0x%016lX\nFraction: 0x%016lX\n\n", 
    num.sign, num.exp, num.frac);
}

int main() {
   float input1, input2;
   floatNum num1, num2, result;

   printf("Enter two floating point numbers\n");
   while (scanf("%f%f", &input1, &input2) != EOF) {
      num1 = unpack(input1);
      printf("First number %f\n", input1);
      print_unpacked_float(num1);

      printf("Second number %f\n", input2);
      num2 = unpack(input2);
      print_unpacked_float(num2);

      printf("Testing addition\n");
      result = single_float_add(num1, num2);
      print_unpacked_float(result);
      printf("Packed float: %f\n\n", pack(result));
      
      printf("Testing subtraction\n");
      result = single_float_subtract(num1, num2);
      print_unpacked_float(result);
      printf("Packed float: %f\n\n", pack(result));

      printf("Testing multiplication\n");
      result = single_float_multiply(num1, num2);
      print_unpacked_float(result);
      printf("Packed float: %f\n\n", pack(result));

      printf("Enter two floating point numbers\n");
   }

   return 0;
}
