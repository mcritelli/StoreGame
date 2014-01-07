#include "FirstState.h"
#define DEBUG false

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

FirstState FirstState::m_FirstState;

const float testVertices[] = 
{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

void FirstState::init()
{

	textRenderer.Init("DINMittelschriftStd.otf");

	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	rx = 0.0f;
	ry = 0.0f;
	rz = 0.0f;
	if (DEBUG) std::cout << "INSIDE FIRST_STATE INIT\n";
	// Setup shader
	std::vector<string> params;
	shader.InitializeShader("cube_vert.glsl", "Frag_SolidColor.glsl", params);

	std::vector<glm::vec3> out_vertex, out_normal;
	ModelLoader testModel;
	testModel.LoadOBJ("cube.obj", out_vertex, out_normal);

	/*int cnt = 0;
	std::cout << "MODEL DATA: \n";
	for (std::vector<glm::vec3>::iterator it = out_vertex.begin(); it != out_vertex.end(); ++it)
	{
		
		if (cnt % 3 == 0)
			std::cout << "------------------------\n";
		std::cout << glm::to_string(*it) << "\n";
		cnt++;
	}

	std::cout << "cnt: " << cnt << "\n";*/
		
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

	

	float fFrustumScale = 1.0f;
	float fzNear = 0.1f;
	float fzFar = 10.0f;

	ProjectionMatrix = glm::perspective(45.0f, (800.0f / 600.0f), fzNear, fzFar);
	CameraMatrix = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	matrixUniform = glGetUniformLocation(shader.m_program, "MVP");
	GLuint colorUnf = glGetUniformLocation(shader.m_program, "inColor");

	glUseProgram(shader.m_program);
	glUniform4f(colorUnf, 1.0f, 0.0f, 0.5f, 0.6f);
	glUseProgram(0);
}

void FirstState::destroy()
{

}

void FirstState::handleEvents(Game* game, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{		
		// Translation
		if (event.key.keysym.sym == SDLK_RIGHT)
			x += 0.1f;
		else if (event.key.keysym.sym == SDLK_LEFT)
			x -= 0.1f;

		if (event.key.keysym.sym == SDLK_UP)
			y += 0.1f;
		else if (event.key.keysym.sym == SDLK_DOWN)
			y -= 0.1f;

		if (event.key.keysym.sym == SDLK_z)
			z += 0.1f;
		else if (event.key.keysym.sym == SDLK_x)
			z -= 0.1f;

		// Rotation
		if (event.key.keysym.sym == SDLK_a)
			rx += 10.0f;
		else if (event.key.keysym.sym == SDLK_s)
			rx -= 10.0f;

		if (event.key.keysym.sym == SDLK_d)
			ry += 10.0f;
		else if (event.key.keysym.sym == SDLK_f)
			ry -= 10.0f;

		if (event.key.keysym.sym == SDLK_g)
			rz += 10.0f;
		else if (event.key.keysym.sym == SDLK_h)
			rz -= 10.0f;
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
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 translationMatrix = glm::translate(glm::vec3(x, y, z));
	glm::mat4 rotationX = glm::rotate(rx, glm::vec3(1, 0, 0));
	glm::mat4 rotationY = glm::rotate(ry, glm::vec3(0, 1, 0));
	glm::mat4 rotationZ = glm::rotate(rz, glm::vec3(0, 0, 1));
	glm::mat4 modelMatrix = translationMatrix * rotationX * rotationY * rotationZ * scaleMatrix;
	glm::mat4 MVP = ProjectionMatrix * CameraMatrix * modelMatrix;


	glBindVertexArray(vaoObject1);
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	
	glBindVertexArray(0);
	glUseProgram(0);
}