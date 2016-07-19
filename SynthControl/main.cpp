#include <SDL.h>
#include "SynthControl.h"

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return 0;
	{
		cSynthControl Controller;
	}
	SDL_Quit();
	return 0;
}