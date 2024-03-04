#pragma once
#include "system.h"
#include "timer.h"
#include "drawable.h"

struct backend
{
public:
	backend() = default;
	backend(int x, int y, int bpp) { }
	virtual bool init() = 0;
	virtual bool clear_color(float r, float g, float b, float a) = 0;
	virtual bool clear() = 0;
	virtual bool swap() = 0;
	virtual bool running() = 0;
	virtual bool display() = 0;
	bool update() { return time->update() && clear() && display() && swap() && running(); }
	std::array<int, 2> size;
	struct time* time;
	struct font* font;
	struct audio* audio;
	std::vector<struct drawable*> drawables;
	~backend()
	{
		for(auto& drawable : drawables)
			delete drawable;
		drawables.clear();
	}
};

