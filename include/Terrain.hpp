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
		void setFrequency(glm::fvec2);
		void generate();


	};

}

#endif //TERRAIN_HPP