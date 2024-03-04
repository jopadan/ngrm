#pragma once

struct time
{
	double acc;
	double last;
	double now;

	struct frame_counter {
		int fps;
		int cnt;
		char str[16];
		frame_counter() : fps(0), cnt(0) { memset(str, '\0', 16); snprintf(str, 16, "FPS: %d\0", fps); }
	} frame;

	time(double seed = 0.0) : acc(seed), last(seed), now(seed) { }
	virtual double get() = 0;
	virtual void set(double t) = 0;

	bool update()
	{
		last = now; now = get();
		acc = acc < 1.0 ? acc + delta() : 0.0;

		if(acc <= 0.0)
		{
			frame.fps = frame.cnt;
			frame.cnt = 0;
			snprintf(frame.str, sizeof(frame.str), "FPS: %d\0", frame.fps);
		}
		else
		{
			frame.cnt++;
		}

		return true;
	}
	
	double delta() { return now - last; }
	double delta(double old) { return now - old; }
};

