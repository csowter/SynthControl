#ifndef mouseeventhandler_h
#define mouseeventhandler_h

class iMouseEventHandler
{
public:
	virtual ~iMouseEventHandler(){};
	virtual void MouseDown(SDL_Event &e){};
	virtual void MouseUp(SDL_Event &e){};
	virtual void MouseMoved(SDL_Event &e){};
};

#endif