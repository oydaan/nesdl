#include "game.h"
#include "resource_manager.h"

/* Create a new game struct */
game_t* game_new(GLuint width, GLuint height) {
	game_t* g = (game_t*)malloc(sizeof(game_t));
	if (g != NULL) {
		memset(g, 0, sizeof(game_t));

		g->height = height;
		g->width = width;
		g->state = GAME_ACTIVE;

		resource_initManager();
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

}

/* Destroy game struct */
void game_destroy(game_t* g) {
	if (g != NULL) {
		free(g);
	}
	
	resource_clear();
	resource_destroy();
}