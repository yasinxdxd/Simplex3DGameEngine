#ifndef SIMPLEX3D_SHADER_HPP
#define SIMPLEX3D_SHADER_HPP

#include "Definations.hpp"
#include <string>

namespace Simplex3D
{
	class Shader
	{
	public:
		explicit Shader();
		explicit Shader(const char* vertex_shader_path, const char* fragment_shader_path);
		~Shader();

	public:
		void use();
		bool loadShader(const char* vertex_shader_path, const char* fragment_shader_path);
		bool attachShader();

	private:
		bool checkShaderCompile(U16& shader);
		bool checkShaderLink(U16& program);

	public:
		//uniforms:
		void uniform1d(const std::string& name, double value ) const;
		void uniform1f(const std::string& name, float value) const;
		void uniform1i(const std::string& name, I16 value) const;
		void uniform1ui(const std::string& name, U16 value) const;
		void uniform2d(const std::string& name, double v0, double v1) const;
		void uniform2f(const std::string& name, float v0, float v1) const;
		void uniform2i(const std::string& name, I16 v0, I16 v1) const;
		void uniform2ui(const std::string& name, U16 v0, U16 v1) const;
		void uniform3d(const std::string& name, double v0, double v1, double v2) const;
		void uniform3f(const std::string& name, float v0, float v1, float v2) const;
		void uniform3i(const std::string& name, I16 v0, I16 v1, I16 v2) const;
		void uniform3ui(const std::string& name, U16 v0, U16 v1, U16 v2) const;
		void uniform4d(const std::string& name, double v0, double v1, double v2, double v3) const;
		void uniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
		void uniform4i(const std::string& name, I16 v0, I16 v1, I16 v2, I16 v3) const;
		void uniform4ui(const std::string& name, U16 v0, U16 v1, U16 v2, U16 v3) const;
		
		//uniform vectors:
		void uniform1dv(const std::string& name, I16 count, const double* value) const;
		void uniform1fv(const std::string& name, I16 count, const float* value) const;
		void uniform1iv(const std::string& name, I16 count, const I16* value) const;
		void uniform1uiv(const std::string& name, I16 count, const U16* value) const;
		void uniform2dv(const std::string& name, I16 count, const double* value) const;
		void uniform2fv(const std::string& name, I16 count, const float* value) const;
		void uniform2iv(const std::string& name, I16 count, const I16* value) const;
		void uniform2uiv(const std::string& name, I16 count, const U16* value) const;
		void uniform3dv(const std::string& name, I16 count, const double* value) const;
		void uniform3fv(const std::string& name, I16 count, const float* value) const;
		void uniform3iv(const std::string& name, I16 count, const I16* value) const;
		void uniform3uiv(const std::string& name, I16 count, const U16* value) const;
		void uniform4dv(const std::string& name, I16 count, const double* value) const;
		void uniform4fv(const std::string& name, I16 count, const float* value) const;
		void uniform4iv(const std::string& name, I16 count, const I16* value) const;
		void uniform4uiv(const std::string& name, I16 count, const U16* value) const;

		//uniform matrices:
		void uniformMatrix2fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix3fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix4fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix2x3fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix3x2fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix2x4fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix4x2fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix3x4fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix4x3fv(const std::string& name, I16 count, bool transpose, const float* value);
		void uniformMatrix2dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix3dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix4dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix2x3dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix3x2dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix2x4dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix4x2dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix3x4dv(const std::string& name, I16 count, bool transpose, const double* value);
		void uniformMatrix4x3dv(const std::string& name, I16 count, bool transpose, const double* value);


	private:
		const char* m_vertex_shader_source;
		const char* m_fragment_shader_source;
		U16 m_vertex_shader;
		U16 m_fragment_shader;
		U16 m_shader_program;
		

	};
}



#endif //SIMPLEX3D_SHADER_HPP