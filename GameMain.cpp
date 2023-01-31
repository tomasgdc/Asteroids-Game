#include "lib\Game.h"
#include "lib\lib.h"
#include "lib\Engine.h"

/*
	TODO:
	//gafferongames.com/game-physics/fix-your-timestep/
*/


void GameMain()
{
	bool bWindowQuit = false;
	Game game;
	
	//Initialize game
	game.Initialize();

	
	game.m_dPreviousTime = Engine::getInstance().GetTimeInMS();
	double lag = 0.0;
	while (!game.IsQuit() && !bWindowQuit)
	{
		game.m_dCurrentTime = Engine::getInstance().GetTimeInMS();
		double elapsed = (game.m_dCurrentTime - game.m_dPreviousTime);
		game.m_dPreviousTime = game.m_dCurrentTime;
		lag += elapsed;

		//Process input
		bWindowQuit = CheckBegin();
		
		int MS_PER_UPDATE = 1000 / game.m_iFramesPerSecond;
		while (lag >= MS_PER_UPDATE)
		{
			game.Update(1.0);
			lag -= MS_PER_UPDATE;
		}
		game.Input();  
		game.Render();

		Flip();
		game.m_iFrameNumber++;
	}
	//Shutdown
}

