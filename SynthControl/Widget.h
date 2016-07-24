#ifndef widget_h
#define widget_h

#include <cstdint>
#include <SDL.h>

class cWidget
{
protected:
	SDL_Rect mBoundingRectangle;
	bool mVisible;

public:
	cWidget() = delete;
	cWidget(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	virtual ~cWidget(){};

	const SDL_Rect& GetBounds() const {	return mBoundingRectangle; }
	bool GetVisible() const { return mVisible; }
	void SetVisible(bool visible) { mVisible = visible; }
	bool ContainsPoint(int32_t x, int32_t y) const;
	
	virtual void MouseDown(SDL_Event &e) = 0;
	virtual void MouseUp(SDL_Event &e) = 0;
	virtual void MouseMove(SDL_Event &e) {};

	virtual void Render(SDL_Renderer *renderer) = 0;
};

#endif