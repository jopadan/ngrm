#pragma once
#include "system.h"

using namespace math::vec;

struct drawable
{
	std::vector<f32<4>>  vertices;
	std::vector<u32<3>>  indices;
	std::vector<f32<4>>  face_normals;
	std::vector<f32<4>>  vertex_normals;
	f32<4> pos;
	f32<4> ext;
	GLuint vbo[2];
	drawable() = default;
	drawable(size_t vcount, size_t fcount, f32<4> position, f32<4> extends) : pos(position), ext(extends), vbo{0,0}
	{
		vertices.resize(vcount);
		indices.resize(fcount * 2);
		face_normals.resize(fcount);
		vertex_normals.resize(fcount * 2);
	}
	virtual ~drawable()
	{
		vertex_normals.clear();
		face_normals.clear();
		indices.clear();
		vertices.clear();
	}
	virtual bool init() = 0;
	virtual bool draw() = 0;
	virtual bool post() = 0;
};
