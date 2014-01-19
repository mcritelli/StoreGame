#include <cstdio>
#include <..\GL\glew.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "Engine\BaseShader.h"
#include "Engine\Game.h"
#include "States\FirstState.h"

#include <CEGUI\CEGUI.h>
#include <CEGUI\System.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>

using namespace CEGUI;

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window = SDL_CreateWindow("OpenGL", 300, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	SDL_Event windowEvent;
	
	OpenGL3Renderer& testRenderer = OpenGL3Renderer::bootstrapSystem();
	DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>(System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("fonts", "GUI\\fonts");
	rp->setResourceGroupDirectory("schemes", "GUI\\schemes");
	rp->setResourceGroupDirectory("imagesets", "GUI\\imagesets");
	rp->setResourceGroupDirectory("layouts", "GUI\\layouts");
	rp->setResourceGroupDirectory("looknfeels", "GUI\\looknfeels");
	
	Font::setDefaultResourceGroup("fonts");
	ImageManager::setImagesetDefaultResourceGroup("imagesets");
	Scheme::setDefaultResourceGroup("schemes");
	WidgetLookManager::setDefaultResourceGroup("looknfeels");
	WindowManager::setDefaultResourceGroup("layouts");

	FontManager::getSingleton().createFromFile("FreeSans.xml");
	SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	Window* myRoot = WindowManager::getSingleton().loadLayoutFromFile("test.layout");
	System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	Window* staticText = myRoot->getChild("FPSCounter");
	staticText->setText("TEST TEXTTESTETSDF");
	//staticText->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(0.25f, 0.0f)));
	glewExperimental = GL_TRUE;
	glewInit();
	
	Game game;
	game.init(FirstState::Instance());
	

	// Main loop
	std::string fpsString = "FPS: 0";
	int c = 100;
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
		
		// Update the FPS counter
		if (game.FPS != game.LAST_FPS)
		{
			fpsString = "FPS: " + std::to_string(game.FPS) + " fps";
			staticText->setText(fpsString.c_str());
		}
		
		
		CEGUI::System::getSingleton().renderAllGUIContexts();
		glDisable(GL_SCISSOR_TEST);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Sends the back buffer to the front buffer for rendering
		SDL_GL_SwapWindow(window);
		
	}
	
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}