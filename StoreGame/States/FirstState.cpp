#include "FirstState.h"
#define DEBUG false

FirstState FirstState::m_FirstState;

void FirstState::init()
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE INIT\n";
	// Setup shader
	std::vector<string> params;
	shader.InitializeShader("vert.glsl", "frag.glsl", params);

	float vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.366f, 0.0f, 1.0f,
		-0.5f, -0.366f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	elapsedTimeUniform = glGetUniformLocation(shader.m_program, "time");
	elapsedTimeUniformFrag = glGetUniformLocation(shader.m_program, "fragTime");
	GLuint loopDurationUnf = glGetUniformLocation(shader.m_program, "loopDuration");
	GLuint loopDurationUnfFrag = glGetUniformLocation(shader.m_program, "fragLoopDuration");
	glUseProgram(shader.m_program);
	glUniform1f(loopDurationUnf, 5.0f);
	glUniform1f(loopDurationUnfFrag, 5.0f);
	glUseProgram(0);
}

void FirstState::destroy()
{

}

void FirstState::handleEvents(Game* game)
{
}

void FirstState::update(Game* game)
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE UPDATE\n";
}

void FirstState::draw(Game* game)
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE DRAW\n";

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader.m_program);

	glUniform1f(elapsedTimeUniform, (game->TIME_CURRENT - game->TIME_START) / 1000.0f);
	glUniform1f(elapsedTimeUniformFrag, (game->TIME_CURRENT - game->TIME_START) / 1000.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}