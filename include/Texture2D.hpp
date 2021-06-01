#ifndef TEXTURE_2D_HPP
#define TEXTURE_2D_HPP

#include "Definitions.hpp"

namespace Simplex3D
{

	class Texture2D
	{
	public:
		explicit Texture2D();
		explicit Texture2D(const char*);
		~Texture2D();

	public:
		operator unsigned int() const noexcept;
		bool loadFromFile(const char*);
	
	private:
		int m_width, m_height, m_nr_channels;
		unsigned char* m_data;
		U32 m_texture;
	};

}

#endif //TEXTURE_2D_HPP
