/* ************************************************************************************************
 * bits.c
 *************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <stdbool.h>
#include <string.h>

#define ISPOWEROFTWO(n) (n && !(n&(n-1)))  // returns true if given number is power of 2 else false

// Bit-fields
typedef struct size
{
    int a:1;    // same 4 bytes
    int b:31;   // same 4 bytes
} mystruct;

/* ************************************************************************************************
 * lowestSetBit
 *      Returns lowest bit Set(1)
 ************************************************************************************************/
int lowestSetBit(int x)
{
    return (x & ~(x-1));
}

/* ************************************************************************************************
 * clearLowestSetBit
 *      Clears the lowest bit Set
 *************************************************************************************************/
int clearLowestSetBit(int x)
{
    return (x & (x-1));
}

/* ************************************************************************************************
 *  lowestBitNotSet 
 *      Return lowest bit NotSet(0)
 *************************************************************************************************/
uint32_t lowestBitNotSet(int x)
{
    return (~x & (x+1));
}

/* ************************************************************************************************
 * signOfNumber
 *************************************************************************************************/
void signOfNumber(int v)
{
    int sign = v >> (sizeof(int) * 8 - 1);
    printf("%d\n", sign);
}

/* ************************************************************************************************
 * No of bits set : Brian Kernighan’s Algorithm:
 * ex. 31 = 11111 -> return 5
 *      8 = 1000 -> return 1
 ************************************************************************************************/
uint32_t noOfSetBits(int n)
{
    int count =0;
    while (n)
    {
        n = (n & (n-1));
        count++;
    }

    return count;
}

/* ************************************************************************************************
 * No of bits set : Lookup table method
 * ex. 31 = 11111 -> return 5
 *      8 = 1000 -> return 1
 *************************************************************************************************/
#define B2(n) n, n+1, n+1, n+2
#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
#define COUNT_BITS   B6(0), B6(1), B6(1), B6(2)

uint32_t BitsSetTable256[256] = {COUNT_BITS};

// another way to build the map
/*
BitsSetTable256[0] = 0;
for (int i = 0; i < 256; i++)
{
    BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];
}
*/

uint32_t countNoOfSetBits(uint32_t v)
{
    int c = BitsSetTable256[v & 0xff] + 
            BitsSetTable256[(v >> 8) & 0xff] + 
            BitsSetTable256[(v >> 16) & 0xff] + 
            BitsSetTable256[v >> 24]; 

    return c;
}

/* ************************************************************************************************
 * FlippedCount
 * Count number of bits to be flipped to convert A to B
 *  ex. input: A = 10 = 00001010
 *  	input: B = 20 = 00010100
 *   -> output = 4
 *      Also known as finding Hamming distance
**************************************************************************************************/
uint32_t FlippedCount(uint32_t a, uint32_t b)
{
    return noOfSetBits(a^b);
}

/* ************************************************************************************************
 * Swap even and odd bits
 *   ex. input: 25 = 11001 -> output 100110
**************************************************************************************************/
uint32_t swapEvenOdd(uint32_t num)
{
    uint32_t even = num & 0xAAAAAAAA;
    uint32_t odd = num & 0x55555555;

    uint32_t swapBits = (even >> 1 | odd << 1);

    return swapBits;
}

/* ************************************************************************************************
* Swap nibbles in byte
   ex. input: 25 = 00011001 -> output 10010001
       input: 0x10101010 -> output 0x01010101
**************************************************************************************************/
uint32_t swapNibbles(uint32_t num)
{
    uint32_t msb = num & 0xF0F0F0F0;
    uint32_t lsb = num & 0x0F0F0F0F;

    uint32_t swapBits = (msb >> 4 | lsb << 4);

    return swapBits;
}

/* ************************************************************************************************
 * addNumbers
 *      Add two integers without + - operator
**************************************************************************************************/
uint32_t addNumbers(uint32_t a, uint32_t b)
{
    int sum = 0;
    
    while (b != 0)
    {
        sum = a^b;
        b = (a&b)<<1;
        a = sum;
    }
    return sum;
}

/* ************************************************************************************************
 * bitExtract
 *************************************************************************************************/
int bitExtract(int number, int k, int p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}

/* ************************************************************************************************
 * reverseBits : Lookup table method
 *      ex. 31 = 11101
 *           8 = 10111
 *************************************************************************************************/
static const unsigned char BitReverseTable256[256] = 
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

uint32_t reverseBitsLookup(uint32_t v)
{
    unsigned int c;                 // c will get v reversed

    unsigned char * p = (unsigned char *) &v;
    unsigned char * q = (unsigned char *) &c;

    q[3] = BitReverseTable256[p[0]]; 
    q[2] = BitReverseTable256[p[1]]; 
    q[1] = BitReverseTable256[p[2]]; 
    q[0] = BitReverseTable256[p[3]];

    return c;
}

/* ************************************************************************************************
 * reverseBits
 *      Reverse bits in an integer
 *          ex. 31 = 11101
 *               8 = 10111
 ************************************************************************************************/
uint32_t reverseBits(uint32_t num)
{
    uint32_t revNum = num;              // revNum will be reversed bits of num
    uint32_t s = sizeof(num)*8 - 1;     // extra shift needed at end

    for (num >>= 1 ; num ; num >>= 1)
    {
        revNum <<= 1;
        revNum |= num & 0x1;
        s--;
    }
    revNum <<= s;                       // shift when v's highest bits are zero
    return revNum;
}

/* ************************************************************************************************
 * primeNumbers
 *************************************************************************************************/
void primeNumbers(uint32_t n)
{
    bool arr[n+1];
    memset(arr, false, sizeof(arr));

    for (int i = 2 ; i*i <= n ; ++i)
    {
        if (arr[i] == false)
        {
            for (int j=i*2 ; j <= n ; j+=i)
            {
                arr[j] = true;              // Mark all the multiples true
            }
        }
    }

    // Print all prime numbers
    for (int i = 2; i <= n ; ++i)
    {
        if (arr[i] == false)
        {
            printf("%d,", i);
        }
    }
    printf("\n");
}

/* ***********************************************************************************************
 * singleNumber
    Given a non-empty array of integers, every element appears twice except for one. 
    Find that single one.
 ************************************************************************************************/
uint32_t singleNumber(uint32_t nums[], uint32_t size)
{
    int result = 0;
    for (int i = 0 ; i < size ; ++i)
    {
        result ^= nums[i];
    }

    return result;
}

/* ***********************************************************************************************
 * missingNumber
    Given a non-empty array of integers, all the numbers are present starting from 1 except one number 
    Find that single one.
 ************************************************************************************************/
uint32_t missingNumber(uint32_t nums[], uint32_t size)
{
    int result = 0;
    int i = 0;
    
    for (i = 0 ; i < size ; ++i)
    {
        result ^= i^nums[i];
    }

    return result^size;
}

/* ***********************************************************************************************
 * bitsMain
 ************************************************************************************************/
int bitsMain()
{
    printf("Hello from bitsMain\n");

    printf("Printing all prime numbers till 100\n");
    primeNumbers(100);

    printf("Number of set bits in 64 : %d\n",countNoOfSetBits(64));

    printf("Addition of 4+5 is : %d\n",addNumbers(4,5));
    
    printf("Reverse for bit pattern is : %x\n",reverseBitsLookup(42));
    
    printf("%d\n", ISPOWEROFTWO(0));
    printf("%d\n", ISPOWEROFTWO(32));

    printf("size of mystruct is = %lu\n", sizeof(mystruct));

    return 0;
}
