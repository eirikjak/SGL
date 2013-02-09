#ifndef game_h
#define game_h



#include <SGL\BaseGame.h>



class Game: public BaseGame
{
public:
	Game();
	
	Game(int argc,char * argv[]);
	~Game(void);
	
	std::string binaryPath;

private:

	int width,height;
	
	


protected:
	void reshape(int width, int height);
	void draw();
	void update(double dt);
	void setup();

	



};

#endif
