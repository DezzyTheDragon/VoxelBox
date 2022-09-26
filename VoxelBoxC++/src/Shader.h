#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>




class Shader
{
private:
	//const std::string filePath = "C:/Users/DestinyG/source/repos/VoxelBoxC++/VoxelBoxC++/shaders/";
	const std::string filePath = "shaders/";
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	//Use/activate shader
	void use();
	void deleteShader();
	//Utility functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif // !SHADER_H