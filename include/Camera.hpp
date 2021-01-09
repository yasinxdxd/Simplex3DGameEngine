#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "Utils.hpp"

struct GLFWwindow;

namespace Simplex3D
{
	

	class Camera
	{
	public:
		Camera();
		~Camera();
		void update(GLFWwindow* window);

	public:///DEGISTIR PUBLIC OLMAYACAK!!!!!!!!
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 direction;

		glm::vec3 up;
		glm::vec3 right_axis;
		glm::vec3 up_axis;
		glm::vec3 front_axis;
	public:///DEGISTIR PUBLIC OLMAYACAK!!!!!!!!
		float pitch, yaw, roll;
		//		x	  y		z 
		//		  rotations


		float camera_speed;
		float rotate_speed;

	public:
		glm::mat4 view;

		//friend class Window;
	};

}

#endif //CAMERA_HPP