/* ************************************************************************************************
* memory.c
**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define my_sizeof(type)     (char*)(&type+1)-(char*)(&type)     // Similar to sizeof

/* ************************************************************************************************
* Offset of element in a structure
* This method is innocuous becuase we do not access any memory location 
* We can use any address instead of 0, then you need to subtract it from the answer 
* Like this : ((size_t)&(((TYPE *)1234)->MEMBER) - 1234)
* ************************************************************************************************/

#define offset_of(TYPE, x)  ((size_t)&(((TYPE*)0)->x))

typedef struct {
    long long a;
    long long b;
    char c;
    char d;
    long long e;
}testType;

// structure A
typedef struct structa_tag
{
    int        c:5;
    int        s:8;
    char        z:1;
} structa_t;

// structure B
typedef struct structb_tag
{
    short int   s;
    char        c;
    int         i;
} structb_t;

// structure C
typedef struct structc_tag
{
    char        c;
    double      d;
    int         s;
} structc_t;

// structure D
typedef struct structd_tag
{
    double      d;
    int         s;
    char        c;
} structd_t;

/* ************************************************************************************************
 * endianness

    higher memoryMain                         
          ----->
    +----+----+----+----+
    |0x01|0x00|0x00|0x00|
    +----+----+----+----+
    ^
    |     Little Endian (LSB in the lower address of memory)
   &x
 *************************************************************************************************/
void endianness()
{
    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c)
    {
        printf("Little endian\n");
    }
    else
    {
        printf("Big endian\n");
    }

    return;
}

uint32_t bigEndianToLittle(uint32_t num)
{
    uint32_t result;

    result = ((num >> 24) & 0xFF)|((num >> 8) & 0xFF00)| \
                ((num << 8) & 0xFF0000)|((num << 24) & 0xFF000000);  
    return result;  
}

/* ************************************************************************************************
 * my_memcpy
 *************************************************************************************************/
void my_memcpy(void* source, void* dest, size_t size)
{
    char* p1 = (char*)source;
    char* p2 = (char*)dest;

    while (size--)
    {
        *p2++ = *p1++;
    }
}

/* **********************************************************************************************
 * my_memcpy_fast
 ************************************************************************************************/
void my_memcpy_fast(void* source, void* dest, size_t size)
{
    uint64_t* u64src = (uint64_t*)source;
    uint64_t* u64dest = (uint64_t*)dest;

    while (size >= sizeof(uint64_t))
    {
        *u64dest++ = *u64src++;
        size -= sizeof(uint64_t);
    }

    char* p2 = (char*)(u64dest);
    char* p1 = (char*)(u64src);

    // copy remaining bytes
    while (size--)
    {
        *p2++ = *p1++;
    }

}
    
size_t my_strlen(const char *str)
{
    size_t len = 0;  
    for (len = 0; str[len]; (len)++);
    return len;
}
/* ************************************************************************************************
 * alignedMalloc
 **************************************************************************************************/
void* alignedMalloc(size_t size, size_t alignment)
{
    // alignment=16,size=20, total=20+16+4=40 bytes allocated
    void *p1 = malloc(size + alignment + sizeof(void*));

    if (p1)
    {
        size_t offset = (size_t)p1 + alignment + sizeof(void*);     // offset = 1+16+4 = 21

        void *p2 = (void*) (offset - (offset % alignment));         // p2 = 21 -(21%16) = 16

        *((size_t*)p2 - 1) = (size_t) p1;   // Airthmetic on void pointer is illegal (size_t)

        return p2;
    }
    return NULL;
}

/* ************************************************************************************************
 * alignedFree
 *************************************************************************************************/
void alignedFree(void* p)
{
    free((void*)(*((size_t*)p-1)));
}

/* ************************************************************************************************
 * stackGrowth
 *************************************************************************************************/
void stackGrowth(int *p)
{
    int i;
    if (!p)
    {
        stackGrowth(&i);
    }
    else if (p < &i)
    {
        printf("Stack grows upward\n");
    }
    else
    {
        printf("Stack grows downward\n");
    }
    return;
}

/* ************************************************************************************************
 * memoryMain
 *************************************************************************************************/
int memoryMain()
{
    printf("Machine is : ");
    endianness();

    int a = 0x78563412;
    printf("0x%x\n", bigEndianToLittle(a));

    stackGrowth(NULL);
    printf("String length is : %zu\n", my_strlen("Hello world"));

    testType myStruct;

    printf("Size is : %lu\n", my_sizeof(myStruct));
    printf("Offset is : %lu\n", offset_of(testType, d));


    printf("sizeof(structa_t) = %lu\n", sizeof(structa_t));
    printf("sizeof(structb_t) = %lu\n", sizeof(structb_t));
    printf("sizeof(structc_t) = %lu\n", sizeof(structc_t));
    printf("sizeof(structd_t) = %lu\n", sizeof(structd_t));

    char arr[11] = "Helloworld";        // Can use malloc
    char brr[11] = {};                  // Can use malloc

    printf("Before copy : %s\n", arr);
    my_memcpy_fast((void*)arr,(void*)brr,10);
    printf("After copy : %s\n", brr);

    return 0;

}





