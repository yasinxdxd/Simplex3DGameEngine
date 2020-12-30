#include "Shader.hpp"
#include "Utils.hpp"
#include <glad/glad.h>

//delete//
#include <iostream>
//delete//

namespace Simplex3D
{
	Shader::Shader():
		m_vertex_shader_source(nullptr), 
		m_fragment_shader_source(nullptr)
	{
		m_shader_program = glCreateProgram();
		m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path):
		m_vertex_shader_source(nullptr), 
		m_fragment_shader_source(nullptr)
	{
		m_shader_program = glCreateProgram();
		m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		loadShader(vertex_shader_path, fragment_shader_path);
	}
	
	Shader::~Shader()
	{
		glDeleteShader(m_vertex_shader);
		glDeleteShader(m_fragment_shader);
		glDeleteProgram(m_shader_program);
	}
	
	void Shader::use()
	{
		glUseProgram(m_shader_program);
		//glUniform1d(,)
	}

	bool Shader::loadShader(const char* vertex_shader_path, const char* fragment_shader_path)
	{
		std::string v = Simplex3D::Utils::loadShaderFromFile(vertex_shader_path);
		std::string f = Simplex3D::Utils::loadShaderFromFile(fragment_shader_path);

		m_vertex_shader_source = v.c_str();
		m_fragment_shader_source = f.c_str();

		glShaderSource(m_vertex_shader, 1, &m_vertex_shader_source, NULL);
		glCompileShader(m_vertex_shader);

		if (!checkShaderCompile(m_vertex_shader))
			return false;

		glShaderSource(m_fragment_shader, 1, &m_fragment_shader_source, NULL);
		glCompileShader(m_fragment_shader);

		if (!checkShaderCompile(m_fragment_shader))
			return false;


		return true;
	}

	bool Shader::attachShader()
	{
		//std::cout << m_vertex_shader << m_fragment_shader << std::endl;
		//Attach shader porgram and vertex shader:
		glAttachShader(m_shader_program, m_vertex_shader);
		//Attach shader porgram and fragment shader:
		glAttachShader(m_shader_program, m_fragment_shader);
		//Linking
		glLinkProgram(m_shader_program);

		if (!checkShaderLink(m_shader_program))
			return false;

		/*if Linking is ok, we don't need shaders anymore*/
		glDeleteShader(m_vertex_shader);
		glDeleteShader(m_fragment_shader);
		return true;

	}

	bool Shader::checkShaderCompile(U16& shader)
	{
		I16  success;
		char infoLogV[256];
		char infoLogF[256];

		/*for control*/
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 256, NULL, infoLogV);
			std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLogV << std::endl;
			glDeleteShader(m_vertex_shader);
			glDeleteShader(m_fragment_shader);
			glDeleteProgram(m_shader_program);
			return false;
		}
		
		return true;

	}

	bool Shader::checkShaderLink(U16& program)
	{
		/*for control the linking*/
		I16  successProgram;
		char infoLogProgram[512];
		glGetProgramiv(program, GL_LINK_STATUS, &successProgram);
		if (!successProgram)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLogProgram);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogProgram << std::endl;
			glDeleteShader(m_vertex_shader);
			glDeleteShader(m_fragment_shader);
			glDeleteProgram(m_shader_program);
			return false;
		}

		return true;
	}


	//uniforms:

	void Shader::uniform1d(const std::string& name, double value) const
	{
		glUniform1d(glGetUniformLocation(m_shader_program, name.c_str()), value);
	}

	void Shader::uniform1f(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_shader_program, name.c_str()), value);
	}

	void Shader::uniform1i(const std::string& name, I16 value) const
	{
		glUniform1i(glGetUniformLocation(m_shader_program, name.c_str()), value);
	}

	void Shader::uniform1ui(const std::string& name, U16 value) const
	{
		glUniform1ui(glGetUniformLocation(m_shader_program, name.c_str()), value);
	}

	void Shader::uniform2d(const std::string& name, double v0, double v1) const
	{
		glUniform2d(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1);
	}

	void Shader::uniform2f(const std::string& name, float v0, float v1) const
	{
		glUniform2f(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1);
	}

	void Shader::uniform2i(const std::string& name, I16 v0, I16 v1) const
	{
		glUniform2i(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1);
	}

	void Shader::uniform2ui(const std::string& name, U16 v0, U16 v1) const
	{
		glUniform2ui(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1);
	}

	void Shader::uniform3d(const std::string& name, double v0, double v1, double v2) const
	{
		glUniform3d(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2);
	}

	void Shader::uniform3f(const std::string& name, float v0, float v1, float v2) const
	{
		glUniform3f(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2);
	}

	void Shader::uniform3i(const std::string& name, I16 v0, I16 v1, I16 v2) const
	{
		glUniform3i(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2);
	}

	void Shader::uniform3ui(const std::string& name, U16 v0, U16 v1, U16 v2) const
	{
		glUniform3ui(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2);
	}

	void Shader::uniform4d(const std::string& name, double v0, double v1, double v2, double v3) const
	{
		glUniform4d(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2, v3);
	}

	void Shader::uniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
	{
		glUniform4f(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2, v3);
	}

	void Shader::uniform4i(const std::string& name, I16 v0, I16 v1, I16 v2, I16 v3) const
	{
		glUniform4i(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2, v3);
	}

	void Shader::uniform4ui(const std::string& name, U16 v0, U16 v1, U16 v2, U16 v3) const
	{
		glUniform4ui(glGetUniformLocation(m_shader_program, name.c_str()), v0, v1, v2, v3);
	}
	
	//uniform vectors:

	void Shader::uniform1dv(const std::string& name, I16 count, const double* value) const
	{
		glUniform1dv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform1fv(const std::string& name, I16 count, const float* value) const
	{
		glUniform1fv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform1iv(const std::string& name, I16 count, const I16* value) const
	{
		glUniform1iv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform1uiv(const std::string& name, I16 count, const U16* value) const
	{
		glUniform1uiv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform2dv(const std::string& name, I16 count, const double* value) const
	{
		glUniform2dv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform2fv(const std::string& name, I16 count, const float* value) const
	{
		glUniform2fv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform2iv(const std::string& name, I16 count, const I16* value) const
	{
		glUniform2iv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform2uiv(const std::string& name, I16 count, const U16* value) const
	{
		glUniform2uiv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform3dv(const std::string& name, I16 count, const double* value) const
	{
		glUniform3dv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform3fv(const std::string& name, I16 count, const float* value) const
	{
		glUniform3fv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform3iv(const std::string& name, I16 count, const I16* value) const
	{
		glUniform3iv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform3uiv(const std::string& name, I16 count, const U16* value) const
	{
		glUniform3uiv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform4dv(const std::string& name, I16 count, const double* value) const
	{
		glUniform4dv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform4fv(const std::string& name, I16 count, const float* value) const
	{
		glUniform4fv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform4iv(const std::string& name, I16 count, const I16* value) const
	{
		glUniform4iv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	void Shader::uniform4uiv(const std::string& name, I16 count, const U16* value) const
	{
		glUniform4uiv(glGetUniformLocation(m_shader_program, name.c_str()), count, value);
	}

	//uniform matrices:

	void Shader::uniformMatrix2fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix3fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix4fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix2x3fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix3x2fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix2x4fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix4x2fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix3x4fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix4x3fv(const std::string& name, I16 count, bool transpose, const float* value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix2dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix2dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix3dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix3dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix4dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix4dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix2x3dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix2x3dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix3x2dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix3x2dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix2x4dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix2x4dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix4x2dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix4x2dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix3x4dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix3x4dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}

	void Shader::uniformMatrix4x3dv(const std::string& name, I16 count, bool transpose, const double* value)
	{
		glUniformMatrix4x3dv(glGetUniformLocation(m_shader_program, name.c_str()), count, transpose, value);
	}




	/*
	void glUniform4ui(	GLI16 location,
 							GLuI16 v0,
 							GLuI16 v1,
 							GLuI16 v2,
 							GLuI16 v3);

	void glUniform4uiv(	GLI16 location,
						GLsizei count,
						const GLuI16 *value);
	
	*/


}


