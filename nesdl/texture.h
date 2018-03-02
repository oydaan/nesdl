#ifndef TEXTURE_H
#define TEXTURE_H

//#include <GL\glew.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
typedef struct texture_t {
	GLuint ID;
	GLuint width, height;
	GLuint internal_fmt;
	GLuint image_fmt;
	GLuint wrap_s;
	GLuint wrap_t;
	GLuint filter_min; // filtering mode if texture pixels < screen pix
	GLuint filter_max; // if texture pix > screen pix
} texture_t;

texture_t* texture_new();
void texture_destroy(texture_t* texture);

void texture_generate(texture_t* texture, GLuint width, GLuint height, unsigned char* data);
void texture_bind(texture_t* texture);

#endif // !TEXTURE_H