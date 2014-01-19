#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "..\glm\glm.hpp"
#include "..\glm\gtc\quaternion.hpp"
#include "..\glm\gtx\quaternion.hpp"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtx\transform.hpp"
#include <iostream>

class Object3D{
public:
	Object3D();
	void rotateOnAxis(glm::vec3 axis, float angle);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void translateOnAxis(glm::vec3 axis, float dist);
	void translateX(float dist);
	void translateY(float dist);
	void translateZ(float dist);
	void setPosition(glm::vec3 newPosition);
	void setScale(const glm::vec3 allScales);
	void setScaleX(const float scale);
	void setScaleY(const float scale);
	void setScaleZ(const float scale);
	void increaseScale(const glm::vec3 allScales);
	glm::vec3 getPosition();
	glm::vec3 getEuler();
	glm::quat getQuaternion();
	glm::vec3 getScale();

	virtual void draw() = 0;
	void update();
protected:
	glm::vec3 m_position;
	glm::quat m_quaternion;
	glm::vec3 m_scale;
	glm::mat4 m_modelMatrix;
	bool m_matrixNeedsUpdate;
};

#endif