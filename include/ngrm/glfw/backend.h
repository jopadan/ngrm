#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstddef>

#include "../backend.h"
#include "timer.h"

struct glfw : backend
{
	/* callbacks */
	static void key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		static int windowed_xpos, windowed_ypos, windowed_width, windowed_height;
		if (action != GLFW_PRESS)
			return;

		if (key == GLFW_KEY_ESCAPE && mods == 0)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		if ((key == GLFW_KEY_ENTER && mods == GLFW_MOD_ALT) ||
				(key == GLFW_KEY_F11 && mods == GLFW_MOD_ALT))
		{
			if (glfwGetWindowMonitor(window))
			{
				glfwSetWindowMonitor(window, NULL,
						windowed_xpos, windowed_ypos,
						windowed_width, windowed_height, 0);
			}
			else
			{
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				if (monitor)
				{
					const GLFWvidmode* mode = glfwGetVideoMode(monitor);
					glfwGetWindowPos(window, &windowed_xpos, &windowed_ypos);
					glfwGetWindowSize(window, &windowed_width, &windowed_height);
					glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
				}
			}
		}
	}
	static void mouse_cb(GLFWwindow* window, int button, int action, int mods)
	{
		if(action == GLFW_PRESS)
			printf("mouse button: %d\n", button);
	}
	static void scroll_cb(GLFWwindow* window, double xoffset, double yoffset)
	{
		static float zoom = 1.0f;
		zoom+=yoffset;
		printf("scroll pos: <%f|%f> zoom: %f\n", xoffset, yoffset, zoom);
		//glTranslatef(0.0f, 0.0f, zoom);
	}
	static void cursor_cb(GLFWwindow* window, double x, double y)
	{
		printf("cursor pos: <%f|%f>\n", x, y);
	}
	static void reshape_cb(GLFWwindow* window, int w, int h)
	{ 
		GLfloat aspect = (GLfloat)w / (h > 0 ? (GLfloat)h : 1.0f);
		GLfloat znear = 0.125f;
		GLfloat zfar = 512.0f;

		glViewport( 0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(45.0f * (float) M_PI / 180.f, aspect, znear, zfar);
		//glFrustum(-xmax, xmax, -xmax*aspect, xmax*aspect, znear, zfar);
	}

	/* constructors */
	glfw(int x, int y, int bpp, const char* title)
	{
		if(!glfwInit())
			exit(EXIT_FAILURE);
		time = new glfw_time();
		if(time == nullptr)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		window = glfwCreateWindow(x, y, title, nullptr, nullptr);
		if(!window) exit(EXIT_FAILURE);
		glfwSetWindowAspectRatio(window, 4, 3);
		/* set callbacks */
		glfwSetFramebufferSizeCallback(window, reshape_cb);
		glfwSetKeyCallback(window, key_cb);
		glfwSetMouseButtonCallback(window, mouse_cb);
		glfwSetCursorPosCallback(window, cursor_cb);
		glfwSetScrollCallback(window, scroll_cb);

		glfwMakeContextCurrent(window);
		gladLoadGL( glfwGetProcAddress );
		glfwSwapInterval(1);
		glfwGetFramebufferSize(window, &size[0], &size[1]);

		reshape_cb(window, size[0], size[1]);
		init();
		clear_color(0.0f, 0.0f, 0.0f, 1.0f);
		clear();
		glfwSetTime( 0.0 );
		//glcContext(glcGenContext());
		//glcScale(10.0f, 10.0f);
	}
	~glfw() { glfwTerminate(); }
	bool running() override { return glfwWindowShouldClose(window) ? false : true; }
	bool clear_color(float r, float g, float b, float a) { glClearColor( r, g, b, a ); return true; }
	bool clear() override
	{ 
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return true;
	}
	bool init() override
	{
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		GLfloat LightAmbient[] = {0.25f, 0.25f, 0.25f, 1.0f};
		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);

		GLfloat LightDiffuse[] = {0.75f, 0.75f, 0.75f, 1.0f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);

		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glShadeModel(GL_SMOOTH);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);

		return true;
	}
	bool swap() override 
	{
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();

		return true;
	}
	bool display() override
	{
		for(auto& drawable : drawables)
		{
			drawable->init();
			drawable->draw();
			drawable->post();
		}

		return true;
	}
	GLFWwindow* window;
	int glc_ctx;
};

void cleanup()
{
	glfwTerminate();
}

