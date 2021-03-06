/*
 * Copyright © 2010 Lubosz Sarnecki
 * Uniform.h
 *
 *  Created on: Dec 16, 2010
 */

#pragma once

#include <string>
#include <vector>
#include "Renderer/OpenGL.h"

using std::string;
using std::vector;

template<typename T>
class Uniform {
 public:
  Uniform() {}
	Uniform(string name, const vector<T> & values): name(name) , values(values) {}
	virtual ~Uniform() {}

	void init(GLuint program);
	string name;
	vector<T> values;
};
