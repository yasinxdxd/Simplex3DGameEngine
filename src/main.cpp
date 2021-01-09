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
#include "Terrain.hpp"

//#include <thread>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>



int main(int argc, char** argv)
{
	Simplex3D::Window myWindow(1920, 1080, "Simplex3D");
	myWindow.setColor(72, 61, 139);
	Simplex3D::Camera cam;

	

	Simplex3D::Model shipModel;
	shipModel.loadModel("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/ship_dark.obj");
	
	Simplex3D::Model pirate("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/pirate_officer.obj");
	
	Simplex3D::Model tower("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/tower.obj");

	Simplex3D::Model chest("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/chest.obj");

    Simplex3D::Model palm("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/OBJ format/palm_short.obj");
    
    Simplex3D::Model teapot("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/teapot.obj");

    //Simplex3D::Model dragon("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/dragonstl.obj");

	Simplex3D::Light light;

    Simplex3D::Terrain terrain;




    /*
    std::ifstream file("C:/Users/Lenovo/Desktop/Coding/RemoteGyroscopePCSide/application.windows64/data.txt");
    std::string line = "";
    std::string prefix = "";
    std::stringstream ss;

    glm::vec3 accelerometerData = glm::vec3(0, 0, 0);
    glm::vec3 gyroscopeData = glm::vec3(0, 0, 0);
    glm::vec3 rotationData = glm::vec3(0, 0, 0);

    std::cout << "here1" << std::endl;
    */
    

    std::ofstream writeFile;

    std::ifstream readFile;
    glm::vec3 pos;
    glm::vec3 angles;
    bool isFileExist;
    readFile.open("save.ini");
    isFileExist = readFile.good();
    if (readFile.is_open())
    {
        if(isFileExist)
            readFile >> pos.x >> pos.y >> pos.z >> angles.x >> angles.y >> angles.z;
    }
    readFile.close();
    if (isFileExist)
    {
        cam.position = pos;
        cam.pitch = angles.x;
        cam.yaw = angles.y;
        cam.roll = angles.z;
    }
    

    glEnable(GL_LIGHTING);

	float a = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (myWindow.isOpen())
	{
		
		myWindow.pollEvent();
		
		cam.update(static_cast<GLFWwindow*>(myWindow));
		
        light.update();

        pirate.update();
		shipModel.update();
		tower.update();
		chest.update();
        palm.update();
        teapot.update();
        terrain.update();
        //dragon.update();


		
		a+=0.4;
        terrain.setScale({ 32,32,32 });
        terrain.setPosition({0,0,0});

        palm.setPosition({ -40,0,60 });
		tower.setPosition({-20,0,50});
		
        shipModel.setPosition({ 0,0,0 });
        //shipModel.setColor({1, 0.1, 0.3, 0.5});

        chest.setPosition({ -30,0,-12 });
		pirate.setPosition({ -25,0,0 });
		//pirate.setRotateX(a);
        pirate.setRotateY(a);
        //pirate.setScale({ 5,5,5 });

        //dragon.setPosition({-100, 60, -25});
        //dragon.setScale({0.1, 0.1 , 0.1 });
        
        teapot.setPosition({-110, 60 ,-12});
        teapot.setRotation(a*2, { 0.1, 1.0, 0.1 });

        light.setPosition({ -100, 60,-12 });
        light.setScale({5,5,5});



        //while(std::getline(file, line))
        





        /*
        file.open("C:/Users/Lenovo/Desktop/Coding/RemoteGyroscopePCSide/application.windows64/data.txt");

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
        */
        



        if (Simplex3D::WindowEvent::Keyboard::isKeyPressed(GLFW_KEY_ESCAPE))
        {
			myWindow.setWindowClose(true);
            writeFile.open("save.ini");
            writeFile << cam.position.x << std::endl;
            writeFile << cam.position.y << std::endl;
            writeFile << cam.position.z << std::endl;

            writeFile << cam.pitch << std::endl;
            writeFile << cam.yaw << std::endl;
            writeFile << cam.roll << std::endl;
            writeFile.close();
        }













		//DRAW:
		myWindow.clear();
        
        light.drawMeshes(myWindow, cam);
        terrain.drawMeshes(myWindow, cam);

		
        shipModel.drawMeshes(myWindow, cam);
		pirate.drawMeshes(myWindow, cam);
		tower.drawMeshes(myWindow, cam);
		chest.drawMeshes(myWindow, cam);
        palm.drawMeshes(myWindow, cam);
        teapot.drawMeshes(myWindow, cam);
        

        //dragon.drawMeshes(myWindow, cam);

		myWindow.display();
	}

	

	return 0;
}


