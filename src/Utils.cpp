#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "Vertex.hpp"

namespace Simplex3D
{

    std::string Utils::loadShaderFromFile(const char* file_path)
    {
        std::string content;
        std::ifstream file_stream(file_path, std::ios::in);

        if (!file_stream.is_open()) {
            std::cerr << "Could not read file " << file_path << " File does not exist." << std::endl;
            return "";
        }

        std::string line = "";
        while (!file_stream.eof())
        {
            std::getline(file_stream, line);
            content.append(line + "\n");
        }

        file_stream.close();
        return content;

    }


    std::vector<Vertex> Utils::loadOBJ(const char* file_path)
    {
        //return value
        std::vector<Vertex> vertices;

        //v,vn,vt values of the .obj files
        std::vector<glm::vec3> position_vertices;
        std::vector<glm::vec2> textcoord_vertices;
        std::vector<glm::vec3> normal_vertices;

        //f values of the .obj files
        std::vector<unsigned int> position_vertices_indices;
        std::vector<unsigned int> textcoord_vertices_indices;
        std::vector<unsigned int> normal_vertices_indices;

        //reading
        std::stringstream ss;
        std::string line = "";
        std::string prefix = "";
        std::fstream file(file_path);

        //temps
        glm::vec3 temp_vec3;
        glm::vec2 temp_vec2;
        unsigned int temp_int;


        //error check
        if (!file.is_open())
            std::cerr << "file couldn't opened!" << std::endl;

        while (std::getline(file, line))
        {
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "#" || prefix == "o" || prefix == "s" || prefix == "g")
                continue;
            else if (prefix == "v")
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                position_vertices.push_back(temp_vec3);
            }
            else if (prefix == "vt")
            {
                ss >> temp_vec2.x >> temp_vec2.y;
                textcoord_vertices.push_back(temp_vec2);
            }
            else if (prefix == "vn")
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                normal_vertices.push_back(temp_vec3);
            }
            else if (prefix == "f")
            {
                unsigned int counter = 0;
                while (ss >> temp_int)
                {
                    if (counter == 0)
                        position_vertices_indices.push_back(temp_int);
                    else if (counter == 1)
                        textcoord_vertices_indices.push_back(temp_int);
                    else if (counter == 2)
                        normal_vertices_indices.push_back(temp_int);

                    if (ss.peek() == '/')
                    {
                        ++counter;
                        ss.ignore(1, '/');
                    }
                    if (ss.peek() == ' ')
                    {
                        ++counter;
                        ss.ignore(1, ' ');
                    }

                    if (counter > 2)
                        counter = 0;
                }

            }
            else
                continue;

        }
        file.close();

        std::cout << position_vertices.size() << std::endl;
        std::cout << textcoord_vertices.size() << std::endl;
        std::cout << normal_vertices.size() << std::endl;

        std::cout << position_vertices_indices.size() << std::endl;
        std::cout << textcoord_vertices_indices.size() << std::endl;
        std::cout << normal_vertices_indices.size() << std::endl;

        vertices.resize(position_vertices_indices.size(), Vertex());

        //setting values of vertex and pushing the vertex in result vertices 
        if ((textcoord_vertices_indices.size() == 0 || textcoord_vertices.size() == 0) && 
             normal_vertices_indices.size() == 0 || normal_vertices.size() == 0)
        {
            for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
            {
                Vertex temp;

                temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
                //temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
                //temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
                temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

                vertices.push_back(temp);
            }
        }
        else if (textcoord_vertices_indices.size() == 0 || textcoord_vertices.size() == 0)
        {
            for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
            {
                Vertex temp;

                temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
                //temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
                temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
                temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

                vertices.push_back(temp);
            }
        }
        else if (normal_vertices_indices.size() == 0 || normal_vertices.size() == 0)
        {
            for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
            {
                Vertex temp;

                temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
                temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
                //temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
                temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

                vertices.push_back(temp);
            }
        }
        else
        {
            for (unsigned int i = 0; i < position_vertices_indices.size(); i++)
            {
                Vertex temp;

                temp.position = position_vertices[fabs(position_vertices_indices[i]) - 1];
                temp.texcoord = textcoord_vertices[fabs(textcoord_vertices_indices[i]) - 1];
                temp.normal = normal_vertices[fabs(normal_vertices_indices[i]) - 1];
                temp.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

                vertices.push_back(temp);
            }
        }

        


        return vertices;
    }

    void Utils::loadOBJEBO(const char* file_path, std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices)
    {
        //return value
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        //v,vn,vt values of the .obj files
        std::vector<glm::vec3> position_vertices;
        std::vector<glm::vec2> textcoord_vertices;
        std::vector<glm::vec3> normal_vertices;

        //f values of the .obj files
        std::vector<unsigned int> position_indices;
        std::vector<unsigned int> texcoord_indices;
        std::vector<unsigned int> normal_indices;

        //reading
        std::stringstream ss;
        std::string line = "";
        std::string prefix = "";
        std::fstream file(file_path);

        //temps
        glm::vec3 temp_vec3;
        glm::vec2 temp_vec2;
        unsigned int temp_int;


        //error check
        if (!file.is_open())
            std::cerr << "file couldn't opened!" << std::endl;

        while (std::getline(file, line))
        {
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "#" || prefix == "o" || prefix == "s" || prefix == "g")
                continue;
            else if (prefix == "v")
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                position_vertices.push_back(temp_vec3);
            }
            else if (prefix == "vt")
            {
                ss >> temp_vec2.x >> temp_vec2.y;
                textcoord_vertices.push_back(temp_vec2);
            }
            else if (prefix == "vn")
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                normal_vertices.push_back(temp_vec3);
            }
            else if (prefix == "f")
            {
                int counter = 0;
                while (ss >> temp_int)
                {
                    //Pushing indices into correct arrays
                    if (counter == 0)
                        position_indices.push_back(temp_int);
                    else if (counter == 1)
                        texcoord_indices.push_back(temp_int);
                    else if (counter == 2)
                        normal_indices.push_back(temp_int);

                    //Handling characters
                    if (ss.peek() == '/')
                    {
                        ++counter;
                        ss.ignore(1, '/');
                    }
                    else if (ss.peek() == ' ')
                    {
                        ++counter;
                        ss.ignore(1, ' ');
                    }

                    //Reset the counter
                    if (counter > 2)
                        counter = 0;
                
                }

            }
            else
                continue;

        }
        file.close();

        std::cout << position_vertices.size() << std::endl;
        std::cout << textcoord_vertices.size() << std::endl;
        std::cout << normal_vertices.size() << std::endl;


        vertices.resize(position_vertices.size(), Vertex());
        indices.resize(position_indices.size());

        //setting values of vertex and pushing the vertex in result vertices 
        for (int i = 0; i < position_vertices.size(); i++)
        {
            Vertex temp;

            temp.position = position_vertices[i];
            //temp.texcoord = textcoord_vertices[i];
            //temp.normal = normal_vertices[i];
            temp.color = glm::vec4(0, 0.5, 0.5, 1);

            vertices.push_back(temp);

        }

        for (int i = 0; i < position_indices.size(); i++)
        {

            indices.push_back(position_indices[i]);
            //indices.push_back(textcoord_vertices_indices[i]);
            //indices.push_back(normal_vertices_indices[i]);

        }

        _vertices = vertices;
        _indices = indices;

    }







    std::vector<Vertex> Utils::loadOBJ2(const char* file_name)
    {
        //Vertex portions
        std::vector<glm::fvec3> vertex_positions;
        std::vector<glm::fvec2> vertex_texcoords;
        std::vector<glm::fvec3> vertex_normals;

        //Face vectors
        std::vector<unsigned int> vertex_position_indicies;
        std::vector<unsigned int> vertex_texcoord_indicies;
        std::vector<unsigned int> vertex_normal_indicies;

        //Vertex array
        std::vector<Vertex> vertices;

        std::stringstream ss;
        std::ifstream in_file(file_name);
        std::string line = "";
        std::string prefix = "";
        glm::vec3 temp_vec3;
        glm::vec2 temp_vec2;
        unsigned int temp_glint = 0;

        //File open error check
        if (!in_file.is_open())
        {
            throw "ERROR::OBJLOADER::Could not open file.";
        }

        //Read one line at a time
        while (std::getline(in_file, line))
        {
            //Get the prefix of the line
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "#")
            {

            }
            else if (prefix == "o")
            {

            }
            else if (prefix == "s")
            {

            }
            else if (prefix == "use_mtl")
            {

            }
            else if (prefix == "v") //Vertex position
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                vertex_positions.push_back(temp_vec3);
            }
            else if (prefix == "vt")
            {
                ss >> temp_vec2.x >> temp_vec2.y;
                vertex_texcoords.push_back(temp_vec2);
            }
            else if (prefix == "vn")
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                vertex_normals.push_back(temp_vec3);
            }
            else if (prefix == "f")
            {
                int counter = 0;
                while (ss >> temp_glint)
                {
                    //Pushing indices into correct arrays
                    if (counter == 0)
                        vertex_position_indicies.push_back(temp_glint);
                    else if (counter == 1)
                        vertex_texcoord_indicies.push_back(temp_glint);
                    else if (counter == 2)
                        vertex_normal_indicies.push_back(temp_glint);

                    //Handling characters
                    if (ss.peek() == '/')
                    {
                        ++counter;
                        ss.ignore(1, '/');
                    }
                    else if (ss.peek() == ' ')
                    {
                        ++counter;
                        ss.ignore(1, ' ');
                    }

                    //Reset the counter
                    if (counter > 2)
                        counter = 0;
                }
            }
            else
            {

            }
        }

        //Build final vertex array (mesh)
        vertices.resize(vertex_position_indicies.size(), Vertex());

        //Load in all indices
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
            //vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
            //vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
            vertices[i].color = glm::vec4(1.f, 1.f, 0.f, 1.f);
        }

        //DEBUG
        std::cout << "Nr of vertices: " << vertices.size() << "\n";

        //Loaded success
        std::cout << "OBJ file loaded!" << "\n";
        return vertices;
    }


    glm::vec3 Utils::readGyroscope(const char* file_path)
    {
        std::ifstream file("D:/PCSide/application.windows64/data.txt");
        std::string line = "";
        std::string prefix = "";
        std::stringstream ss;

        glm::vec3 accelerometerData = glm::vec3(0, 0, 0);
        glm::vec3 gyroscopeData = glm::vec3(0, 0, 0);
        glm::vec3 rotationData = glm::vec3(0, 0, 0);

        std::cout << "here1" << std::endl;
        file.open("D:/PCSide/application.windows64/data.txt");

        if (!file.is_open())
        {
            throw "ERROR::OBJLOADER::Could not open file.";
        }

        while (std::getline(file, line))
        {
            std::cout << "here2" << std::endl;
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "aX:")
            {
                ss << accelerometerData.x;
            }
            else if (prefix == "aY:")
            {
                ss << accelerometerData.y;
            }
            else if (prefix == "aZ:")
            {
                ss << accelerometerData.z;
            }
            
            if (prefix == "gX:")
            {
                ss << gyroscopeData.x;
            }
            else if (prefix == "gY:")
            {
                ss << gyroscopeData.y;
            }
            else if (prefix == "gZ:")
            {
                ss << gyroscopeData.z;
            }

            if (prefix == "rX:")
            {
                ss << rotationData.x;
            }
            else if (prefix == "rY:")
            {
                ss << rotationData.y;
            }
            else if (prefix == "rZ:")
            {
                ss << rotationData.z;
            }


            std::cout << accelerometerData.x << '\n';

        }
        file.close();
            

        return rotationData;

    }



}
