#pragma once

#include "../timer.h"
#include <GLFW/glfw3.h>

struct glfw_time : time
{
	glfw_time(double init = 0.0) { last = init; now = init; set(init); }
	double get() override { return glfwGetTime(); }
	void set(double t) override { glfwSetTime(t); };
};

