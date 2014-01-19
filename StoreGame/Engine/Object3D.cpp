#include "Object3D.h"

/**********************************************************************************************//**
 * @fn	Object3D::Object3D(void)
 *
 * @brief	Default constructor.
 *
 * @author	Mcritelli
 * @date	1/19/2014
 **************************************************************************************************/

Object3D::Object3D(void)
{
	m_matrixNeedsUpdate = false;
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_quaternion = glm::quat();

	m_modelMatrix = glm::translate(m_position) * glm::toMat4(m_quaternion) * glm::scale(m_scale);
}

/**********************************************************************************************//**
 * @fn	void Object3D::rotateOnAxis(glm::vec3 axis, float angle)
 *
 * @brief	Rotate around arbitrary axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	axis 	The axis.
 * @param	angle	The angle.
 **************************************************************************************************/

void Object3D::rotateOnAxis(glm::vec3 axis, float angle)
{
	m_quaternion *= glm::angleAxis(angle, axis);
	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
 * @fn	void Object3D::rotateX(float angle)
 *
 * @brief	Rotate object around X axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	angle	The angle in degrees.
 **************************************************************************************************/

void Object3D::rotateX(float angle)
{
	rotateOnAxis(glm::vec3(1, 0, 0), angle);
}

/**********************************************************************************************//**
 * @fn	void Object3D::rotateY(float angle)
 *
 * @brief	Rotate object around Y axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	angle	The angle in degrees.
 **************************************************************************************************/

void Object3D::rotateY(float angle)
{
	rotateOnAxis(glm::vec3(0, 1, 0), angle);
}

/**********************************************************************************************//**
 * @fn	void Object3D::rotateZ(float angle)
 *
 * @brief	Rotate object around Z axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	angle	The angle in degrees.
 **************************************************************************************************/

void Object3D::rotateZ(float angle)
{
	rotateOnAxis(glm::vec3(0, 0, 1), angle);
}

/**********************************************************************************************//**
 * @fn	void Object3D::translateOnAxis(glm::vec3 axis, float dist)
 *
 * @brief	Translate object on an arbitrary axis. Axis assumed to be normalized.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	axis	The axis.
 * @param	dist	The distance.
 **************************************************************************************************/

void Object3D::translateOnAxis(glm::vec3 axis, float dist)
{
	m_position += (axis * dist);
	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
 * @fn	void Object3D::translateX(float dist)
 *
 * @brief	Translate object on X axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	dist	The distance to translate by.
 **************************************************************************************************/

void Object3D::translateX(float dist)
{
	translateOnAxis(glm::vec3(1, 0, 0), dist);
}

/**********************************************************************************************//**
 * @fn	void Object3D::translateY(float dist)
 *
 * @brief	Translate object on Y axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	dist	The distance to translate by.
 **************************************************************************************************/

void Object3D::translateY(float dist)
{
	translateOnAxis(glm::vec3(0, 1, 0), dist);
}

/**********************************************************************************************//**
 * @fn	void Object3D::translateZ(float dist)
 *
 * @brief	Translate object on Z axis.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @param	dist	The distance to translate by.
 **************************************************************************************************/

void Object3D::translateZ(float dist)
{
	translateOnAxis(glm::vec3(0, 0, 1), dist);
}

/**********************************************************************************************//**
 * @fn	void Object3D::scale(void)
 *
 * @brief	Scales this object.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 **************************************************************************************************/

void Object3D::setScale(const glm::vec3 scale)
{
	m_scale.x = scale.x;
	m_scale.y = scale.y;
	m_scale.z = scale.z;

	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
 * @fn	void Object3D::setScaleX(float scale)
 *
 * @brief	Sets X scale.
 *
 * @author	Mcritelli
 * @date	1/19/2014
 *
 * @param	scale	The scale.
 **************************************************************************************************/

void Object3D::setScaleX(const float scale)
{
	m_scale.x = scale;
	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
* @fn	void Object3D::setScaleY(float scale)
*
* @brief	Sets Y scale.
*
* @author	Mcritelli
* @date	1/19/2014
*
* @param	scale	The scale.
**************************************************************************************************/

void Object3D::setScaleY(const float scale)
{
	m_scale.y = scale;
	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
* @fn	void Object3D::setScaleZ(float scale)
*
* @brief	Sets Z scale.
*
* @author	Mcritelli
* @date	1/19/2014
*
* @param	scale	The scale.
**************************************************************************************************/

void Object3D::setScaleZ(const float scale)
{
	m_scale.z = scale;
	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
 * @fn	glm::vec3 Object3D::getPosition(void)
 *
 * @brief	Gets the position.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @return	Vec3 containing this object's position.
 **************************************************************************************************/

glm::vec3 Object3D::getPosition(void)
{
	return m_position;
}

/**********************************************************************************************//**
 * @fn	glm::vec3 Object3D::getEuler(void)
 *
 * @brief	Gets the euler angles for the current orientation.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @return	Vec3 containing this object's euler angles.
 **************************************************************************************************/

glm::vec3 Object3D::getEuler(void)
{
	return glm::eulerAngles(m_quaternion);
}

/**********************************************************************************************//**
 * @fn	glm::quat Object3D::getQuaternion(void)
 *
 * @brief	Gets the quaternion.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @return	Quaternion describing this object's orientation.
 **************************************************************************************************/

glm::quat Object3D::getQuaternion(void)
{
	return m_quaternion;
}

/**********************************************************************************************//**
 * @fn	glm::vec3 Object3D::getScale(void)
 *
 * @brief	Gets the scale.
 *
 * @author	Mcritelli
 * @date	1/17/2014
 *
 * @return	Vector containing current scale parameters.
 **************************************************************************************************/

glm::vec3 Object3D::getScale(void)
{
	return m_scale;
}

/**********************************************************************************************//**
 * @fn	void Object3D::increaseScale(const glm::vec3 allScales)
 *
 * @brief	Adds to existing scaling factors.
 *
 * @author	Mcritelli
 * @date	1/19/2014
 *
 * @param	allScales	The scale increase on all 3 axes.
 **************************************************************************************************/

void Object3D::increaseScale(const glm::vec3 allScales)
{
	m_scale.x += allScales.x;
	m_scale.y += allScales.y;
	m_scale.z += allScales.z;

	m_matrixNeedsUpdate = true;
}

/**********************************************************************************************//**
 * @fn	void Object3D::update(void)
 *
 * @brief	Updates this object.
 *
 * @author	Mcritelli
 * @date	1/19/2014
 **************************************************************************************************/

void Object3D::update()
{
	//std::cout << "INSIDE OBJECT3D UPDATE\n";
	if (m_matrixNeedsUpdate)
	{
		m_modelMatrix = glm::translate(m_position) * glm::toMat4(m_quaternion) * glm::scale(m_scale);
		m_matrixNeedsUpdate = false;
		//std::cout << "\tMATRIX UPDATED\n";
	}
}

/**********************************************************************************************//**
 * @fn	void Object3D::setPosition(glm::vec3 newPosition)
 *
 * @brief	Sets the position of this object.
 *
 * @author	Mcritelli
 * @date	1/19/2014
 *
 * @param	newPosition	The new position.
 **************************************************************************************************/

void Object3D::setPosition(glm::vec3 newPosition)
{
	m_position.x = newPosition.x;
	m_position.y = newPosition.y;
	m_position.z = newPosition.z;

	m_matrixNeedsUpdate = true;
}

