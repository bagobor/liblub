/*
 * Copyright © 2010 Lubosz Sarnecki
 * Input.h
 *
 *  Created on: Sep 28, 2010
 */

#pragma once

class Input {
 public:
  float inputSpeed, mouseSensitivity;
	virtual void eventLoop() = 0;
};
