#ifndef FIRSTSTATE_H
#define FIRSTSTATE_H

#include "..\Engine\State.h"
#include "..\Engine\Game.h"
#include "..\Engine\BaseShader.h"

using namespace std;

class FirstState : public State{
public:
	void init();
	void destroy();
	void draw(Game* game);
	void update(Game* game);
	void handleEvents(Game* game);

	static State* Instance() {
		return &m_FirstState;
	}
protected:
	FirstState(){}
private:
	static FirstState m_FirstState;
	BaseShader shader;
	
};

#endif