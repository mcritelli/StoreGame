#include "Cube.h"

/**********************************************************************************************//**
 * @file	Objects\Cube.cpp
 *
 * @brief	Implements the cube class.
 **************************************************************************************************/

Cube::Cube(void)
{
	
}

void Cube::Init()
{
	m_shader.InitializeShader("cube_vert.glsl", "Frag_SolidColor.glsl");
	std::vector<glm::vec3> out_vertex, out_normal;
	ModelLoader* model;
	model->LoadOBJ("cube.obj", out_vertex, out_normal);
	model = 0;

	vertexCount = out_vertex.size();

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_vertex.size() * sizeof(glm::vec3), &out_vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_normal.size() * sizeof(glm::vec3), &out_normal[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoObject1);
	glBindVertexArray(vaoObject1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Temporary - this will be abstracted into its own Camera class
	float fFrustumScale = 1.0f;
	float fzNear = 0.1f;
	float fzFar = 10.0f;

	ProjectionMatrix = glm::perspective(45.0f, (800.0f / 600.0f), fzNear, fzFar);
	CameraMatrix = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);

	matrixUniform = glGetUniformLocation(m_shader.m_program, "MVP");
	GLuint colorUnf = glGetUniformLocation(m_shader.m_program, "inColor");

	glUseProgram(m_shader.m_program);
	glUniform4f(colorUnf, 1.0f, 0.0f, 0.5f, 0.6f);
	glUseProgram(0);
}

void Cube::draw()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);


	glUseProgram(m_shader.m_program);
	
	glm::mat4 MVP = ProjectionMatrix * CameraMatrix * m_modelMatrix;

	glBindVertexArray(vaoObject1);
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

void Cube::update(float dt)
{
	//std::cout << "INSIDE CUBE UPDATE\n";
	Object3D::update();
}