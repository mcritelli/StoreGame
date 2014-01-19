#include "..\Engine\Object3D.h"
#include "..\Engine\ModelLoader.h"
#include "..\Engine\BaseShader.h"
#include <iostream>

#include <..\GL\glew.h>
#include "..\glm\glm.hpp"

class Cube : public Object3D
{
public:
	Cube();
	void Init();
	void update(float dt);
	void draw();
private:
	BaseShader m_shader;
	GLuint vertexBuffer, matrixUniform, indexBuffer, normalBuffer;
	GLuint vaoObject1, vaoObject2;
	int vertexCount;
	glm::mat4 ProjectionMatrix, CameraMatrix;
};