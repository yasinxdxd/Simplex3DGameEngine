#include "Window.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "WindowEvent.hpp"
#include "Utils.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "Terrain.hpp"
#include "EngineGUI.hpp"
#include "BatchRenderer.hpp"
#include "Texture2D.hpp"
#include "CubeMap.hpp"
#include "LOD.hpp"
#include "Log.hh"


#include <exception>
#include <array>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>




int main(int argc, char* argv[])
{
    printf("argc ======= %d", argc);
    Simplex3D::Window myWindow(1080, 720, "Simplex3D");
    if (argc > 1)
    {
        if (strcmp(argv[1], "!fullscreen") == 0)   //C style :)
        {
            myWindow.setFullScreen(true);
            
        }
    }
	myWindow.setColor(200,200,200);
    Simplex3D::EngineGUI::getInstace()->Init(myWindow);

    ///////////////////////////////////////CUBE MAP/////////////////////////////////////////////
    /**/Simplex3D::Shader cubeMapShader;
    /**/cubeMapShader.loadShader("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/CubeMapV.glsl", "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/glsl/CubeMapF.glsl");
    /**/cubeMapShader.attachShader();
    /**/
    /**/const char* paths[6] = { "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/textures/space/SpaceboxCollection/Spacebox1/_left.png",
                                "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/textures/space/SpaceboxCollection/Spacebox1/_right.png",
                                "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/textures/space/SpaceboxCollection/Spacebox1/_top.png" ,
                                "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/textures/space/SpaceboxCollection/Spacebox1/_bottom.png" ,
                                "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/textures/space/SpaceboxCollection/Spacebox1/_front.png" ,
                                "C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/textures/space/SpaceboxCollection/Spacebox1/_back.png" };
    /**/
    /**/
    /**/
    /**/Simplex3D::CubeMap cubeMap1;
    /**/cubeMap1.loadFromFile(paths);
    ////////////////////////////////////////////////////////////////////////////////////////////



	Simplex3D::Camera cam;

    Simplex3D::Texture2D texture_sun("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_sun.jpg");
    Simplex3D::Texture2D texture_venus("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_venus_surface.jpg");
    Simplex3D::Texture2D texture_jupiter("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_jupiter.jpg");
    Simplex3D::Texture2D texture_mars("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_mars.jpg");
    Simplex3D::Texture2D texture_mercury("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_mercury.jpg");
    Simplex3D::Texture2D texture_neptune("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_neptune.jpg");
    Simplex3D::Texture2D texture_saturn("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_saturn.jpg");
    Simplex3D::Texture2D texture_uranus("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\back.jpg");
    Simplex3D::Texture2D texture_earth("C:\\Users\\Lenovo\\Desktop\\freelance\\opengl solar system\\2k_earth_daymap.jpg");


    
    Simplex3D::Light light;


    Simplex3D::Model model_sun;
    Simplex3D::Model model_venus;
    Simplex3D::Model model_jupiter;
    Simplex3D::Model model_mars;
    Simplex3D::Model model_mercury;
    Simplex3D::Model model_neptune;
    Simplex3D::Model model_saturn;
    Simplex3D::Model model_uranus;
    Simplex3D::Model model_earth;

    model_sun.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_venus.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_jupiter.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_mars.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_mercury.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_neptune.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_saturn.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_uranus.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");
    model_earth.loadModelOBJ("C:/Users/Lenovo/Desktop/Coding/3DSolution/3DGameEngine/resources/3D/sphere.obj");



    model_sun.setTexture(texture_sun);
    model_venus.setTexture(texture_venus);
    model_jupiter.setTexture(texture_jupiter);
    model_mars.setTexture(texture_mars);
    model_mercury.setTexture(texture_mercury);
    model_neptune.setTexture(texture_neptune);
    model_saturn.setTexture(texture_saturn);
    model_uranus.setTexture(texture_uranus);
    model_earth.setTexture(texture_earth);
    

    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(light, "light");

    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_sun, "sun");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_venus, "venus,");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_jupiter, "jupiter");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_mars, "mars");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_mercury, "mercury");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_neptune, "neptune");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_saturn, "saturn");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_uranus, "uranus");
    Simplex3D::EngineGUI::getInstace()->componentList.addEntity(model_earth, "earth");






    //std::vector<Simplex3D::Entity*> e;

    //e.push_back(shipModel);

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
    glm::vec3 pos(0, 0, 0);
    glm::vec3 angles(0, 0, 0);
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
    
    log("hey");

	float a = 0.01;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (myWindow.isOpen())
	{
		
		myWindow.pollEvent();
		
		cam.update(static_cast<GLFWwindow*>(myWindow));
        /*
        coord.update();
        light.update();

        pirate.update();
        //e[0]->update();
        //shipModel->update();
		tower.update();
		chest.update();
        palm.update();
        teapot.update();
        terrain.update();
        //dragon.update();
        

        //e[0]->setPosition({ Simplex3D::EngineGUI::getInstace()->componentList.pos,0,0 });
		
		a+=0.4;
        terrain.setScale({ 320,320,320 });
        terrain.setPosition({-100,-117.5,-100});
        palm.setPosition({ -40,0,60 });
		tower.setPosition({-20,0,50});
        chest.setPosition({ -30,0,-12 });
		pirate.setPosition({ -25,0,0 });
        pirate.setRotateY(a);
        teapot.setPosition({-110, 60 ,-12});
        teapot.setRotation(a*2, { 0.1, 1.0, 0.1 });

        light.setPosition({ -100, 1600,-12 });
        light.setScale({5,5,5});
        */

        
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

        //entities[0].update();
        //entities[0].setPosition({ pos, 0, 0 });

        Simplex3D::EngineGUI::getInstace()->update();
		//DRAW:
        myWindow.clear();
        cubeMap1.draw(myWindow, cam, glm::mat4(1), cubeMapShader, glm::vec3());

        
        for(U16 i = 0; i < Simplex3D::EngineGUI::getInstace()->componentList.entityGUIs.size(); i++)
            Simplex3D::EngineGUI::getInstace()->componentList.entityGUIs[i]->entity->drawMeshes(myWindow, cam, light.getPosition());
		
        //batcRenderer.draw(myWindow, cam, glm::mat4(1.0f), light.getPosition());

        Simplex3D::EngineGUI::getInstace()->render();
		myWindow.display();
	}

    //delete shipModel;

	return 0;
}


