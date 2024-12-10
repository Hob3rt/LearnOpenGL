#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h> 
#include <glfw/glfw3.h>
#include "stb_image.h"
class TextureData
{
public:
	TextureData(char const* path);
	TextureData(std::vector<std::string> faces);
	~TextureData();

public:
	unsigned int ID;
	std::string type;

	enum Type {
		TEXTURE2D,
		TEXTURECUBE,
		NONE
	};
private:

};

