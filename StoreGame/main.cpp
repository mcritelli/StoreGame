#include <cstdio>
#include <..\GL\glew.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "Engine\BaseShader.h"
#include "Engine\Game.h"
#include "States\FirstState.h"


int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window = SDL_CreateWindow("OpenGL", 300, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	SDL_Event windowEvent;
	
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	Game game;
	game.init(FirstState::Instance());
	

	// Main loop
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			game.handleEvents(windowEvent);
			if (windowEvent.type == SDL_QUIT) break;
			if (windowEvent.type == SDL_KEYUP)
			{
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
			}
		}

		game.update();
		game.draw();

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Sends the back buffer to the front buffer for rendering
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}