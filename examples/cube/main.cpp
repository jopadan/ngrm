#if   defined( GLFW )
#include <ngrm/glfw/backend.h>
#endif

#include <ngrm/cube.h>

struct backend* backend = nullptr;

int main(int argc, char** argv)
{
	backend = new glfw(800, 600, 32, "glteramoo");
	backend->init();
	backend->drawables.push_back(new cube());
	do
	{
	} while(backend->update());

	exit(EXIT_SUCCESS);
}

