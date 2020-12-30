#include "Window.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "WindowEvent.hpp"
#include "Utils.hpp"
#include <exception>
#include <vector>
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Light.hpp"

//#include <thread>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>



int main(int argc, char** argv)
{
	Simplex3D::Window myWindow(1920, 1080, "Simplex3D", true);
	myWindow.setColor(50,50,50);
	Simplex3D::Camera cam;

	

	Simplex3D::Model shipModel;
	shipModel.loadModel("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/ship_dark.obj");
	
	Simplex3D::Model pirate("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/pirate_officer.obj");
	
	Simplex3D::Model tower("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/tower.obj");

	Simplex3D::Model chest("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/chest.obj");
	
	Simplex3D::Light light;
	//std::cout<< Simplex3D::Utils::readGyroscope("D:/PCSide/application.windows64/data.txt").x <<std::endl;





    std::ifstream file("D:/PCSide/application.windows64/data.txt");
    std::string line = "";
    std::string prefix = "";
    std::stringstream ss;

    glm::vec3 accelerometerData = glm::vec3(0, 0, 0);
    glm::vec3 gyroscopeData = glm::vec3(0, 0, 0);
    glm::vec3 rotationData = glm::vec3(0, 0, 0);

    std::cout << "here1" << std::endl;




	float a = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (myWindow.isOpen())
	{
		
		myWindow.pollEvent();
		
		cam.update(myWindow);
		pirate.update();
		shipModel.update();
		tower.update();
		chest.update();

		if (Simplex3D::WindowEvent::Keyboard::isKeyPressed(GLFW_KEY_ESCAPE))
			myWindow.setWindowClose(true);
		
		a+=0.2;

		tower.setPosition({-20,0,50});
		shipModel.setPosition({ 0,0,0 });
		chest.setPosition({ -30,0,-12 });
		pirate.setPosition({ -25,0,0 });
		//pirate.setRotateX(a);
		pirate.setRotateY(a);
		











        file.open("D:/PCSide/application.windows64/data.txt");

        if (!file.is_open())
        {
            throw "ERROR::OBJLOADER::Could not open file.";
        }

        while (std::getline(file, line))
        {
            //std::cout << "here2" << std::endl;
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "aX:")
            {
                ss >> accelerometerData.x;
            }
            else if (prefix == "aY:")
            {
                ss >> accelerometerData.y;
            }
            else if (prefix == "aZ:")
            {
                ss >> accelerometerData.z;
            }

            if (prefix == "gX:")
            {
                ss >> gyroscopeData.x;
            }
            else if (prefix == "gY:")
            {
                ss >> gyroscopeData.y;
            }
            else if (prefix == "gZ:")
            {
                ss >> gyroscopeData.z;
            }

            if (prefix == "rX:")
            {
                ss >> rotationData.x;
            }
            else if (prefix == "rY:")
            {
                ss >> rotationData.y;
            }
            else if (prefix == "rZ:")
            {
                ss >> rotationData.z;
            }


            //std::cout << accelerometerData.x << '\n';

        }
        file.close();



        cam.pitch = -rotationData.y;
        cam.yaw = rotationData.x-90;
        cam.roll = rotationData.z;


















		//DRAW:
		myWindow.clear();
		//me.draw(myWindow, cam);
		shipModel.drawMeshes(myWindow, cam);
		pirate.drawMeshes(myWindow, cam);
		tower.drawMeshes(myWindow, cam);
		chest.drawMeshes(myWindow, cam);

		myWindow.display();
	}

	

	return 0;
}


