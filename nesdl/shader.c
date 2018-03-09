#include "shader.h"

#include <stdio.h>

/* Create a new shader object */
shader_t* shader_new() {
	shader_t* s = (shader_t*)malloc(sizeof(shader_t));
	if (s != NULL) {
		memset(s, 0, sizeof(shader_t));
	}
	return s;
}

/* Delete a shader object */
void shader_destroy(shader_t* shader) {
	if (shader != NULL) free(shader);
}


shader_t* shader_use(shader_t* shader) {
	glUseProgram(shader->ID);
	return shader;
}

void shader_compile(shader_t* shader, const GLchar* vertexSrc, const GLchar* fragmentSrc, const GLchar* geometrySrc) {
	GLuint sVert, sFrag, sGeom;

	// vertex shader
	sVert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVert, 1, &vertexSrc, NULL);
	glCompileShader(sVert);
	shader_checkCompileErrors(sVert, "VERTEX");
	
	// fragment shader
	sFrag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFrag, 1, &fragmentSrc, NULL);
	glCompileShader(sFrag);
	shader_checkCompileErrors(sFrag, "FRAGMENT");

	// compile geometry shader if source code is present
	if (geometrySrc != NULL) {
		sGeom = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sGeom, 1, &geometrySrc, NULL);
		glCompileShader(sGeom);
		shader_checkCompileErrors(sGeom, "GEOMETRY");
	}

	// shader program
	shader->ID = glCreateProgram();
	glAttachShader(shader->ID, sVert);
	glAttachShader(shader->ID, sFrag);
	if (geometrySrc != NULL) {
		glAttachShader(shader->ID, sGeom);
	}
	glLinkProgram(shader->ID);
	shader_checkCompileErrors(shader->ID, "PROGRAM");

	// delete shaders, they're now linked 
	// and no longer necessary
	glDeleteShader(sVert);
	glDeleteShader(sFrag);
	if (geometrySrc != NULL) {
		glDeleteShader(sGeom);
	}
}

void shader_setFloat(shader_t* shader, const GLchar *name, GLfloat value, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void shader_setInt(shader_t* shader, const GLchar *name, GLint value, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
void shader_setVector2f_s(shader_t* shader, const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform2f(glGetUniformLocation(shader->ID, name), x, y);
}

void shader_setVector2f(shader_t* shader, const GLchar *name, const vec3 value, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform2f(glGetUniformLocation(shader->ID, name), value[0], value[1]);
}
void shader_setVector3f_s(shader_t* shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform3f(glGetUniformLocation(shader->ID, name), x, y, z);
}
void shader_setVector3f(shader_t* shader, const GLchar *name, const vec3 value, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform3f(glGetUniformLocation(shader->ID, name), value[0], value[1], value[2]);
}
void shader_setVector4f_s(shader_t* shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform4f(glGetUniformLocation(shader->ID, name), x, y, z, w);
}
void shader_setVector4f(shader_t* shader, const GLchar *name, const vec4 value, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniform4f(glGetUniformLocation(shader->ID, name), value[0], value[1], value[2], value[3]);
}
void shader_setMatrix4(shader_t* shader, const GLchar *name, const mat4 matrix, GLboolean useShader) {
	if (useShader) {
		shader_use(shader);
	}
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, matrix[0]);
}
void shader_checkCompileErrors(GLuint object, char* type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			fprintf(stderr, "| ERROR::SHADER: Compile-time error: Type: %s\n", type);
			fprintf(stderr, "\n -- --------------------------------------------------- -- \n");
			fflush(stderr);
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			fprintf(stderr, "| ERROR::Shader: Link-time error: Type: %s\n", type);
			fprintf(stderr, "\n -- --------------------------------------------------- -- \n");
			fflush(stderr);
		}
	}
}