#ifndef SIMPLEX3D_SKELETON_HPP
#define SIMPLEX3D_SKELETON_HPP

#include <Mesh.hpp>

namespace Simplex3D
{
	class Joint
	{
		glm::vec3 pos;
		std::vector<glm::vec3> rotations;
	};

	class Bone
	{
		Shared<Mesh> mesh;
		Joint joints[2];
	};

	class Skeleton
	{
	public:
		Skeleton();

	private:
		std::vector<Bone> bones;
		
	};
}



#endif //SIMPLEX3D_SKELETON_HPP