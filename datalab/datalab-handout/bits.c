/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
    rr
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 011010  100101         r 111110m how to or
  // 110110  001001 
  int temp = ~(~x & ~y);
  int secondtemp = ~(x & y);
  // 101100  ~010010   101101
  return temp & secondtemp;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //32 bit system, Tmin->Binary; 1000000 000000 
  return 1<<31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  //Tmax -> 01111111111 -> 100000000


  // int nottmin = ~ (1<<31);
  // // handle 0
  // // the sign bit will not include for operation, need to consider special case 0xFFFFF
  // // 000000 ^ 011111 -> 000101
  // return !(x^nottmin);

  int i = x+1;//Tmin,1000...
  x=x+i;//-1,1111...
  x=~x;//0,0000...
  i=!i;//exclude x=0xffff...
  x=x+i;//exclude x=0xffff...
  return !x;

}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  //0b10101010101010101010101010101010
  //0b11111111111111111111111111111111
  //even bit
  //0b01010101010101010101010101010101
  int mask = 0xAA+(0xAA<<8);
  mask=mask+(mask<<16);
  //first set other bits to 0;
  x = x & mask;
  return !(x ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1 ) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // 1 

  return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */

 // 0x39 = 0b00111001
 // 0x30 = 0b00110000
 // 0x9 - x last four binary digits, then get the signed bit, if signed bit is zero, means it is 1.

 //firstly copmare the first two digits 0011 ^ x, -> 0000
 //
int isAsciiDigit(int x) {
    // Firstly compare the 0x3 bit
    // 0x30 -> 00110000
    int tenthdigit = (x >> 4) ^ 3; //-> 0
    //set bit to x
    int single_digit = ~( x & 15)+1;
    int ans = (9 + single_digit);
    int res = ans & (1 << 31);
    int val = !( res | tenthdigit);
    return val;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int temp = !(x);
    int result;
    temp = (~temp) + 1;
    result = (~temp) & y;
    return result | ( (temp) & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // the case when the symbol is different
    // i want x becomes negative 
    // want y becomes positive
    // negate of 0, negate of 001 -> 11111111
    int x_sign = x & (1 << 31); // 0
    int y_sign = y & (1 << 31); // 0
    // i want this to be 
    //first case
    // 1. if y is + amd x is -, 0 if y is - and x is +
    // !(x_sign)-. 1->0
    // !(y_sign)-. 0 ->1
    int f_sign = !(y_sign) & !(!(x_sign));
    // 0. if y is - and x is +, 1 otherwise
    // 
    int s_sign = !(!(x_sign) & !(!(y_sign)));
    // !(x_sign)-. 0 ->1
    // !(y_sign)-. 1 ->0
    int addition;
    x = ~x + 1;
    addition = y + x;
    //comapre the first digit
    // 1. negative-> return 0, 
    //01111111111111111111111111111111
    //10000000000000000000000000000000
    //00000000000000000000000000000001
    //11111111111111111111111111111111 -> overflow in 32 bits machine, consider the case of different symbols then
    addition = !(addition & (1<<31));
    


    //handle special case, overflow of Tmax

    // if negative -> 1; 
    return (addition | f_sign) & s_sign;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // the complement of 0 is still 0, compare with the sign bit,. any other will be 0xfff + 1 = 0

  return ( ((x | (~x + 1)) >> 31) + 1);


}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    //if a positive value, find the Max number 1 in the x then add 1.
    // 12 -> 1100 


    //if a negative value,  1101, 101, find the largest 
    int b16, b8, b4, b2, b1, b0;
    int sign = x >> 31;
    x = (sign & ~x) | (~sign & x);//如果x为正则不变，否则按位取反（这样好找最高位为1的，原来是最高位为0的，这样也将符号位去掉了）


    // 不断缩小范围
    b16 = !!(x >> 16) << 4;//高十六位是否有1
    x = x >> b16;//如果有（至少需要16位），则将原数右移16位
    b8 = !!(x >> 8) << 3;//剩余位高8位是否有1
    x = x >> b8;//如果有（至少需要16+8=24位），则右移8位
    b4 = !!(x >> 4) << 2;//同理
    x = x >> b4;
    b2 = !!(x >> 2) << 1;
    x = x >> b2;
    b1 = !!(x >> 1);
    x = x >> b1;
    b0 = x;
    return b16 + b8 + b4 + b2 + b1 + b0 + 1;//+1表示加上符号位
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int exp = (uf & 0x7f800000) >> 23;
    int sign = uf & (1 << 31);
    if (exp == 0) return uf << 1 | sign;
    if (exp == 255) return uf;
    exp++;
    if (exp == 255) return 0x7f800000 | sign;
    return (exp << 23) | (uf & 0x807fffff);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int s_    = uf>>31;
  int exp_  = ((uf&0x7f800000)>>23)-127;
  int frac_ = (uf&0x007fffff)|0x00800000;
  if(!(uf&0x7fffffff)) return 0;

  if(exp_ > 31) return 0x80000000;
  if(exp_ < 0) return 0;

  if(exp_ > 23) frac_ <<= (exp_-23);
  else frac_ >>= (23-exp_);

  if(!((frac_>>31)^s_)) return frac_;
  else if(frac_>>31) return 0x80000000;
  else return ~frac_+1;


  
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  if(x<=-150)   // bias is 127. -127 - 23 (32 max float bit) 
  return 0;
  else if(x<=-127)
  return (1<<23)>>(-126-x); // 1.0 * 2^-x
  else if(x<=127)//0x7f = 01111111
  return (0x7f+x)<<23; //127 + E << 23 to get the exp
  else
  return 0x7f800000u;
}
