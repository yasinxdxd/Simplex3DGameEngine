#include "Camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>

namespace Simplex3D
{

	Camera::Camera():
		position({ -30.f, 30.f, -30.0f }),
		right_axis({ 1.0f, 0.0f, 0.0f }),
		front_axis({ 0.0f, 0.0f, -1.0f }),
		up_axis({ 0.0f, 1.0f, 0.0f } ),
		up({ 0.0f, 1.0f, 0.0f })
	{ 
		camera_speed = 5.f;
		rotate_speed = 0.5;
		//rotation angles:
		pitch = 0;	//x
		yaw = -90;	//y
		roll = 0;	//z

		
	
	}

	Camera::~Camera()
	{ }

	void Camera::update(GLFWwindow* window)
	{

		//Utils::readGyroscope("D:/PCSide/application.windows64/data.txt");

		//movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += camera_speed * front_axis;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= camera_speed * front_axis;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= camera_speed * right_axis;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += camera_speed * right_axis;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			position += camera_speed * up_axis;
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			position -= camera_speed * up_axis;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera_speed = 16.f; 
			rotate_speed = 1;
		}
		else
		{
			camera_speed = 8.f;
			rotate_speed = 0.3;
		}
		
		
		view = glm::lookAt(position, position + front_axis, up_axis);
		
		//rotate
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			pitch += rotate_speed * 2;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			pitch -= rotate_speed * 2;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			yaw -= rotate_speed * 2;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			yaw += rotate_speed * 2;


		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front_axis = glm::normalize(direction);
		right_axis = glm::normalize(glm::cross(-up, direction));
		//up_axis = glm::cross(direction, right_axis);
		
		

		//view = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}

}