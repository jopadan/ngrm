#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <cstdint>

#if defined(__i386__) || defined(__x86_64__)
#include <experimental/simd>
#endif

#include <cmath>
#include <ctime>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#ifdef GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

#include <GL/glcorearb.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "math.h"

//#include <GL/glc.h>
