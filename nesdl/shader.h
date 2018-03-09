// shader.h

#ifndef SHADER_H
#define SHADER_H

#include <string.h>
//#include <GL\glew.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm\cglm.h>

typedef struct shader_t {
	GLuint ID;
} shader_t;

shader_t* shader_new();
void shader_destroy(shader_t* shader);

shader_t* shader_use(shader_t* shader);
void shader_compile(shader_t* shader, const GLchar* vertexSrc, const GLchar* fragmentSrc, const GLchar* geometrySrc);
void shader_setFloat(shader_t* shader, const GLchar *name, GLfloat value, GLboolean useShader); //false
void shader_setInt(shader_t* shader, const GLchar *name, GLint value, GLboolean useShader);//  = false);
void shader_setVector2f_s(shader_t* shader, const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader); // false);
void shader_setVector2f(shader_t* shader, const GLchar *name, const vec3 value, GLboolean useShader); // false);
void shader_setVector3f_s(shader_t* shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader); // false);
void shader_setVector3f(shader_t* shader, const GLchar *name, const vec3 value, GLboolean useShader); // false);
void shader_setVector4f_s(shader_t* shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader);// = false);
void shader_setVector4f(shader_t* shader, const GLchar *name, const vec4 value, GLboolean useShader);// = false);
void shader_setMatrix4(shader_t* shader, const GLchar *name, const mat4 matrix, GLboolean useShader);// = false);
void shader_checkCompileErrors(GLuint object, char* type);

#endif // !SHADER_H