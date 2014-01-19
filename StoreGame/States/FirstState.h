#ifndef FIRSTSTATE_H
#define FIRSTSTATE_H

#include "..\Engine\State.h"
#include "..\Engine\Game.h"
#include "..\Engine\BaseShader.h"
#include "..\glm\mat4x4.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"
#include "..\glm\gtx\string_cast.hpp"

#include "..\Engine\ModelLoader.h"
#include "..\Objects\Cube.h"

using namespace std;

class FirstState : public State{
public:
	void init();
	void destroy();
	void draw(Game* game);
	void update(Game* game);
	void handleEvents(Game* game, SDL_Event event);

	static State* Instance() {
		return &m_FirstState;
	}
protected:
	FirstState(){}
private:
	static FirstState m_FirstState;
	BaseShader shader;
	GLuint vertexBuffer, matrixUniform, indexBuffer, normalBuffer;
	GLuint vaoObject1, vaoObject2;
	float x, y, z;
	float rx, ry, rz;
	glm::mat4 ProjectionMatrix, CameraMatrix;
	int vertexCount;
	float sx, sy;
	Cube testCube;
};

#endif