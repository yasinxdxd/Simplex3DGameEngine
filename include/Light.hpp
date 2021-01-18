#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"

namespace Simplex3D
{
	
	class Light : public Entity
	{
	public:
		Light();
		~Light();

		//virtual void drawMeshes(Window& window, Camera cam) override;
	};

}

#endif //LIGHT_HPP