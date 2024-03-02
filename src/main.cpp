#if   defined( GLFW )
#include "ngrm/backend/glfw/backend.h"
#endif

#include "ngrm/geometry/cube.h"

struct backend* backend = nullptr;

int main(int argc, char** argv)
{
	backend = new glfw(800, 600, 32, "ngrm");
	backend->init();
	backend->drawables.push_back(new cube());
	do
	{
	} while(backend->update());

	exit(EXIT_SUCCESS);
}

