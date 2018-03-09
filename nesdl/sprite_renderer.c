#include "sprite_renderer.h"


sprite_renderer_t* renderer_new(shader_t* shader)
{
	sprite_renderer_t* renderer = (sprite_renderer_t*)malloc(sizeof(sprite_renderer_t));
	if (!renderer) {
		fprintf(stderr, "Sprite Renderer ctor failed.\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	renderer->shader = shader;
	renderer_initRenderData(renderer);

	return renderer;
}

void renderer_destroy(sprite_renderer_t* renderer)
{
	glDeleteVertexArrays(1, &(renderer->quadVAO));
}

void renderer_drawSprite(sprite_renderer_t* renderer, texture_t* texture, vec3 position, vec3 size, GLfloat rotate, vec3 color)
{
	//size[0] = 10;
	//size[1] = 10;
	//rotate = 0.0f;
	//color = GLM_VEC3_ONE_INIT;

	// prepare transformations
	shader_use(renderer->shader);
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	position[2] = 0.0f; // ensure empty z coordinates
	glm_translate(model, position);
	
	// translation vector
	vec3 tv = GLM_VEC3_ZERO_INIT;
	tv[0] = 0.5f * size[0];
	tv[1] = 0.5f * size[1];

	// Move origin of rotation to center of quad
	glm_translate(model, tv);

	// rotation vector
	vec3 rv = { 0.0f, 0.0f, 1.0f };
	
	// Rotate
	glm_rotate(model, rotate, rv);

	// translation vector
	vec3 tv2 = GLM_VEC3_ZERO_INIT;
	tv2[0] = -0.5f * size[0];
	tv2[1] = -0.5f * size[1];

	// move origin back
	glm_translate(model, tv2);

	// scale vector
	vec3 sv;
	glm_vec_copy(size, sv);
	sv[2] = 1.0f;

	// last scale
	glm_scale(model, sv);

	shader_setMatrix4(renderer->shader, "model", model, GL_FALSE);

	// render textured quad
	shader_setVector3f(renderer->shader, "spriteColor", color, GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	texture_bind(texture);

	glBindVertexArray(renderer->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void renderer_initRenderData(sprite_renderer_t* renderer)
{
	// configure VAO/VBO
	GLuint VBO;
	GLfloat verts[] = {
		// POS		// TEX
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &(renderer->quadVAO));
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindVertexArray(renderer->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}