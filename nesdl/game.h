#ifndef GAME_H
#define GAME_H

//#include <GL\glew.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// current state of the game
typedef enum {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
} gamestate;

// game struct represents all game-related state
// and functionality.
typedef struct game_t {
	gamestate state;
	GLboolean keys[1024];
	GLuint width, height;
} game_t;

game_t* game_new(GLuint width, GLuint height);

// gameloop functions
void game_processInput(game_t* g, GLfloat dt);
void game_update(game_t* g, GLfloat dt);
void game_render(game_t* g);

void game_destroy(game_t* g);

#endif // !GAME_H