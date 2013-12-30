#include "FirstState.h"
#define DEBUG false

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

const int numberOfVertices = 36;

#define RIGHT_EXTENT 0.8f
#define LEFT_EXTENT -RIGHT_EXTENT
#define TOP_EXTENT 0.20f
#define MIDDLE_EXTENT 0.0f
#define BOTTOM_EXTENT -TOP_EXTENT
#define FRONT_EXTENT -1.25f
#define REAR_EXTENT -1.75f

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData[] = {
	//Object 1 positions
	LEFT_EXTENT, TOP_EXTENT, REAR_EXTENT,
	LEFT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
	RIGHT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
	RIGHT_EXTENT, TOP_EXTENT, REAR_EXTENT,

	LEFT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,
	LEFT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
	RIGHT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
	RIGHT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,

	LEFT_EXTENT, TOP_EXTENT, REAR_EXTENT,
	LEFT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
	LEFT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,

	RIGHT_EXTENT, TOP_EXTENT, REAR_EXTENT,
	RIGHT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
	RIGHT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,

	LEFT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,
	LEFT_EXTENT, TOP_EXTENT, REAR_EXTENT,
	RIGHT_EXTENT, TOP_EXTENT, REAR_EXTENT,
	RIGHT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,

	//Object 2 positions
	TOP_EXTENT, RIGHT_EXTENT, REAR_EXTENT,
	MIDDLE_EXTENT, RIGHT_EXTENT, FRONT_EXTENT,
	MIDDLE_EXTENT, LEFT_EXTENT, FRONT_EXTENT,
	TOP_EXTENT, LEFT_EXTENT, REAR_EXTENT,

	BOTTOM_EXTENT, RIGHT_EXTENT, REAR_EXTENT,
	MIDDLE_EXTENT, RIGHT_EXTENT, FRONT_EXTENT,
	MIDDLE_EXTENT, LEFT_EXTENT, FRONT_EXTENT,
	BOTTOM_EXTENT, LEFT_EXTENT, REAR_EXTENT,

	TOP_EXTENT, RIGHT_EXTENT, REAR_EXTENT,
	MIDDLE_EXTENT, RIGHT_EXTENT, FRONT_EXTENT,
	BOTTOM_EXTENT, RIGHT_EXTENT, REAR_EXTENT,

	TOP_EXTENT, LEFT_EXTENT, REAR_EXTENT,
	MIDDLE_EXTENT, LEFT_EXTENT, FRONT_EXTENT,
	BOTTOM_EXTENT, LEFT_EXTENT, REAR_EXTENT,

	BOTTOM_EXTENT, RIGHT_EXTENT, REAR_EXTENT,
	TOP_EXTENT, RIGHT_EXTENT, REAR_EXTENT,
	TOP_EXTENT, LEFT_EXTENT, REAR_EXTENT,
	BOTTOM_EXTENT, LEFT_EXTENT, REAR_EXTENT,

	//Object 1 colors
	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	RED_COLOR,
	RED_COLOR,
	RED_COLOR,

	GREY_COLOR,
	GREY_COLOR,
	GREY_COLOR,

	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,

	//Object 2 colors
	RED_COLOR,
	RED_COLOR,
	RED_COLOR,
	RED_COLOR,

	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,

	GREY_COLOR,
	GREY_COLOR,
	GREY_COLOR,
	GREY_COLOR,
};

const GLshort indexData[] =
{
	0, 2, 1,
	3, 2, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	11, 13, 12,

	14, 16, 15,
	17, 16, 14,
};

FirstState FirstState::m_FirstState;

void FirstState::init()
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE INIT\n";
	// Setup shader
	std::vector<string> params;
	shader.InitializeShader("cube_vert.glsl", "cube_frag.glsl", params);

	

	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoObject1);
	glBindVertexArray(vaoObject1);

	size_t colorDataOffset = sizeof(float)* 3 * numberOfVertices;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);

	glGenVertexArrays(1, &vaoObject2);
	glBindVertexArray(vaoObject2);

	size_t posDataOffset = sizeof(float)* 3 * (numberOfVertices / 2);
	colorDataOffset += sizeof(float)* 4 * (numberOfVertices / 2);

	//Use the same buffer object previously bound to GL_ARRAY_BUFFER.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)posDataOffset);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	float fFrustumScale = 1.0f;
	float fzNear = 0.5f;
	float fzFar = 3.0f;

	glm::mat4 ProjectionMatrix = glm::perspective(45.0f, (800.0f / 600.0f), fzNear, fzFar);

	matrixUniform = glGetUniformLocation(shader.m_program, "modelMatrix");
	GLuint perspectiveMatrixUnf = glGetUniformLocation(shader.m_program, "perspectiveMatrix");
	
	glUseProgram(shader.m_program);
	glUniformMatrix4fv(perspectiveMatrixUnf, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	glUseProgram(0);
}

void FirstState::destroy()
{

}

void FirstState::handleEvents(Game* game, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_a)
		{
			std::cout << "TEST TEXT\n";
		}
	}
}

void FirstState::update(Game* game)
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE UPDATE\n";
}

void FirstState::draw(Game* game)
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE DRAW\n";

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader.m_program);
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));
	glm::mat4 translationMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 finalMatrix = translationMatrix * scaleMatrix;
	glBindVertexArray(vaoObject1);
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, glm::value_ptr(translationMatrix));
	//glUniform3f(offsetUniform, 0.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(vaoObject2);
	translationMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -0.25f));
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, glm::value_ptr(translationMatrix));
	//glUniform3f(offsetUniform, 0.0f, 0.0f, -0.25f);
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
	
	glBindVertexArray(0);
	glUseProgram(0);
}