#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Entity.hpp"

namespace Simplex3D
{
	
	class Terrain : public Entity
	{
	public:
		Terrain();
		~Terrain();
	public:
		void setHigh();
		void setFrequency();



	};

}

#endif //TERRAIN_HPP