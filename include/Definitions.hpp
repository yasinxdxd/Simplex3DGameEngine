/*
DATA TYPE					SIZE(IN BYTES)						RANGE
*********					**************						*****

SHORT INT					2									- 32, 768 TO 32, 767
UNSIGNED SHORT INT			2									0 TO 65, 535
U16				4									0 TO 4, 294, 967, 295
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

#include <sys/types.h>
#include <cstdint>

//Unsigned defines:
using U64 = uint64_t;
using U32 = uint32_t;
using U16 = uint16_t;
using U8 = uint8_t;


//Signed defines:
using I64 = int64_t;
using I32 = int32_t;
using I16 = int16_t;
using I8 = int8_t;



using F32 = float;


//
#include "Vertex.hpp"
#include <vector>
typedef std::vector<Simplex3D::Vertex> VertexArray;
typedef std::vector<unsigned int> IndexArray;


#include <memory>
template<typename _Ptr>
using Unique = std::unique_ptr<_Ptr>;
template<typename _Ptr>
using Shared = std::shared_ptr<_Ptr>;



#endif //SIMPLEX3D_DEFINATIONS_HPP




