//#define GLEW_STATIC

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "game.h"
#include "resource_manager.h"

/* GLFW Function Prototypes */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

game_t* game;

int main(int argc, char* argv[])
{
	game = game_new(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	// basic window construction
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(320, 240, "nesdl", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "window error");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	//glewExperimental = GL_TRUE;
	//glewInit();
	//glGetError();

	glfwSetKeyCallback(window, key_callback);

	// glad loader
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// opengl config
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set callback
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// timing
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// calc delta time
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		// handle user input
		game_processInput(game, deltaTime);

		// update game state
		game_update(game, deltaTime);

		// render
		glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		game_render(game);
		
		// swap buffers
		glfwSwapBuffers(window);
	}

	game_destroy(game);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			game->keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE) {
			game->keys[key] = GL_FALSE;
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
