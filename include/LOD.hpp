#ifndef LOD_HPP
#define LOD_HPP

#include "Entity.hpp"

namespace priv
{

	class LOD : public Simplex3D::Entity
	{
	public:
		LOD();
		~LOD();
		void generate();
	private:
	};

}

#endif //LOD_HPP