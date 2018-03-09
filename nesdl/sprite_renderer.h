#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm\cglm.h>

#include "texture.h"
#include "shader.h"

typedef struct sprite_renderer_t {
	shader_t* shader;
	GLuint quadVAO;
} sprite_renderer_t;

/* Constructor (inits shaders/shapes) */
sprite_renderer_t* renderer_new(shader_t* shader);

/* Destructor */
void renderer_destroy(sprite_renderer_t* renderer);

/* Renders a defined quad textured with given sprite */
void renderer_drawSprite(sprite_renderer_t* renderer, texture_t* texture, vec3 position, vec3 size, GLfloat rotate , vec3 color);

/* Initialize and configure buffer and vert attributes */
void renderer_initRenderData(sprite_renderer_t* renderer);
#endif // !SPRITE_RENDERER

