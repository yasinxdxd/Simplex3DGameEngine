/*
DATA TYPE					SIZE(IN BYTES)						RANGE
*********					**************						*****

SHORT INT					2									- 32, 768 TO 32, 767
UNSIGNED SHORT INT			2									0 TO 65, 535
UNSIGNED INT				4									0 TO 4, 294, 967, 295
INT							4									- 2, 147, 483, 648 TO 2, 147, 483, 647
LONG INT					8									- 2, 147, 483, 648 TO 2, 147, 483, 647
UNSIGNED LONG INT			8									0 TO 4, 294, 967, 295
LONG LONG INT				8									- (2 ^ 63) TO(2 ^ 63) - 1
UNSIGNED LONG LONG INT		8									0 TO 18, 446, 744, 073, 709, 551, 615
SIGNED CHAR					1									- 128 TO 127
UNSIGNED CHAR				1									0 TO 255
FLOAT						4
DOUBLE						8
LONG DOUBLE					12
WCHAR_T						2 OR 4								1 WIDE CHARACTER
*/

#ifndef SIMPLEX3D_DEFINATIONS_HPP
#define SIMPLEX3D_DEFINATIONS_HPP

//Unsigned defines:
typedef unsigned long long int U64;
typedef unsigned long int U32;
typedef unsigned int U16;
typedef unsigned char U8;


//Signed defines:
typedef signed long long int I64;
typedef signed long int I32;
typedef signed int I16;
typedef signed char I8;



typedef float F32;

#endif //SIMPLEX3D_DEFINATIONS_HPP




