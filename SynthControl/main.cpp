#include <SDL.h>
#include "SynthControl.h"

int main(int , char *[])
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		return 0;
	{
		cSynthControl Controller;
	}
	SDL_Quit();
	return 0;
}