#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

static sprite_renderer_t* renderer;

/* Create a new game struct */
game_t* game_new(GLuint width, GLuint height) {
	game_t* g = (game_t*)malloc(sizeof(game_t));
	if (g != NULL) {
		memset(g, 0, sizeof(game_t));

		g->height = height;
		g->width = width;
		g->state = GAME_ACTIVE;

		resource_initManager();
		// load shaders
		resource_loadShader("shaders/sprite.vert",
			"shaders/sprite.frag", NULL, "sprite");
		// config shaders
		mat4 proj;
		glm_ortho(0.0f, (float)g->width, (float)g->height, 0.0f, 
			-1.0f, 1.0f, proj);
		
		shader_t* s = resource_getShader("sprite");
		shader_setInt(shader_use(s), "image", 0, false);
		shader_setMatrix4(s, "projection", proj, false);

		// load textures
		resource_loadTexture("textures/awesomeface.png", GL_TRUE, "img");

		// set render controls
		renderer = renderer_new(s);
	}
	return g;
}

/* Handle user input */
void game_processInput(game_t* g, GLfloat dt)
{

}

/* Update game state */
void game_update(game_t* g, GLfloat dt)
{

}

/* Render game state to screen */
void game_render(game_t* g)
{
	// vector pos, size, color
	vec3 vp = { 200, 200, 0 };
	vec3 vs = { 300, 400, 0 };
	vec3 vc = { 0.0f, 1.0f, 0.0f };
	texture_t* tex = resource_getTexture("img");
	renderer_drawSprite(renderer, tex, vp, vs, 45.0f, vc);
}

/* Destroy game struct */
void game_destroy(game_t* g) {
	if (g != NULL) {
		free(g);
	}
	
	resource_clear();
	resource_destroy();
	renderer_destroy(renderer);
}