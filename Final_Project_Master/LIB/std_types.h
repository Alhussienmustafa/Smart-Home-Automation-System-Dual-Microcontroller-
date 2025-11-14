#ifndef STD_TYPES_H
#define STD_TYPES_H

/* NULL pointer definition */
#ifndef NULL_Ptr
#define NULL_PTR ((void*)0)
#define NULL 0
#endif
/*
 * False value definition
 */
#ifndef False
#define False (0u)
#endif

/*
 * True value definition
 */
#ifndef True
#define True (1u)
#endif

/*
 * boolean data type definition
 */
typedef unsigned char bool;

/* Logical value declaration */
typedef enum{
	LOW = (0u), HIGH = (1u)
}Logical_Value;

typedef short unsigned int u16;
typedef short signed int s16;
typedef long unsigned int u32;
typedef long signed int s32;
typedef float f32;
typedef double f64;
typedef unsigned char u8;
typedef signed char s8;

#endif
