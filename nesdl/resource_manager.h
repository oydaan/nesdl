#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string.h>
//#include <GL\glew.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "texture.h"
#include "shader.h"

typedef struct texture_resource texture_resource;
typedef struct shader_resource shader_resource;
typedef struct resource_manager resource_manager;

void resource_initManager();
shader_t* resource_loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, const char* name);
shader_t* resource_getShader(char* name);
texture_t* resource_loadTexture(const GLchar* file, GLboolean alpha, const char* name);
texture_t* resource_getTexture(char* name);
void resource_clear();
void resource_destroy();

#endif // !RESOURCE_MANAGER_H

