#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

texture_t* texture_new() {
	texture_t* t = (texture_t*)malloc(sizeof(texture_t));
	if (t != NULL) {
		memset(t, 0, sizeof(texture_t));

		t->width = 0;
		t->height = 0;
		t->internal_fmt = GL_RGB;
		t->image_fmt = GL_RGB;
		t->wrap_s = GL_REPEAT;
		t->filter_min = GL_LINEAR;
		t->filter_max = GL_LINEAR;

		glGenTextures(1, &t->ID);
	}

	return t;
}

void texture_destroy(texture_t* texture) {
	if (texture != NULL) free(texture);
}

void texture_generate(texture_t* texture, GLuint width, GLuint height, unsigned char* data) {
	texture->width = width;
	texture->height = height;

	// create texture
	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_fmt, width, height, 0, texture->image_fmt, GL_UNSIGNED_BYTE, data);

	// set texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filter_max);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_bind(texture_t* texture) {
	glBindTexture(GL_TEXTURE_2D, texture->ID);
}