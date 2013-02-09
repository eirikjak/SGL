#ifndef GAME_H
#define GAME_H
#include <SGL\BaseGame.h>
class Game:BaseGame
{
public:
	Game(int argc, char* argv[]);
	~Game(void);

	void draw() ;
	void update(double dt);
	void reshape(int width, int height);
	void setup();
};

#endif