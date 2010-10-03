/*
 * TextureFactory.h
 *
 *  Created on: Mar 25, 2010
 *      Author: bmonkey
 */

#pragma once

#include <string>
#include <vector>
#include "common.h"
#include "Texture.h"
#include "Singleton.h"

class TextureFactory : public Singleton<TextureFactory>{
public:
	Texture * depthTexture(GLuint width, GLuint height, string name);
	Texture * colorTexture(GLuint width, GLuint height, string name);
	Texture * load(string filename, string name);
	Texture * loadCubeMap(string filename, string name);
	Texture * splatTexture(string name, int resolution);
private:
	friend class Singleton<TextureFactory>;
	vector<Texture*> textures;
	GLenum textureEnums[32];
	unsigned textureCount;

	TextureFactory();
	virtual ~TextureFactory();
};

