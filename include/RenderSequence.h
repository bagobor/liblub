/*
 * RenderSequence.h
 *
 *  Created on: Oct 4, 2010
 *      Author: bmonkey
 */

#pragma once

#include "common.h"
#include "FrameBuffer.h"
#include "Materials.h"
#include "RenderPasses.h"

class RenderSequence {
private:
	FrameBuffer *fbo;
	Material * minimal;

public:
	vector<RenderPass*> renderPasses;

	RenderSequence();
	virtual ~RenderSequence();
	void render();

};

