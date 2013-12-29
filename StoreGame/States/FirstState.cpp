#include "FirstState.h"
#define DEBUG false

FirstState FirstState::m_FirstState;

void FirstState::init()
{
	if (DEBUG) std::cout << "INSIDE FIRST_STATE INIT\n";
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
}