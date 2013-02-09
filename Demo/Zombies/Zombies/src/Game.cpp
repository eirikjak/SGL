#include "Game.h"


Game::Game(int argc, char* argv[]):BaseGame()
{

	init("Game",1280,720);
}


void Game::draw() {

	glClearColor(0.4,0.4,0.4,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	swapBuffers();

}
void Game::update(double dt){



}
void Game::reshape(int width, int height){


}
void Game::setup(){


}

Game::~Game(void)
{
}
