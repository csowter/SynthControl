#include <SDL.h>
#include "SynthControl.h"

int main(int , char *[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return 0;
	{
		cSynthControl Controller;
	}
	SDL_Quit();
	return 0;
}