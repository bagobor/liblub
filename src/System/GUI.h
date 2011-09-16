/*
 * GUI.h
 *
 *  Created on: Mar 6, 2011
 *      Author: bmonkey
 */

#pragma once

#include <string>
#include <QImage>
#include "common/Singleton.h"
#include "Scene/Node.h"
#include "Material/Texture.h"
#include <QMap>
#include <QPainter>
using std::string;

class GUI {
public:
  QMap<string,string> textLines;
  QImage * image;
  Node * node;
  ShaderProgram * shader;
  QRectF textBox;
  QSize screenSize;
  QImage black;
  Texture *texture;
  QRectF drawBox;
  GUI();
  virtual ~GUI();
  void addText(string id, string value);
  void updateText(string id, string value);
  void render();
  void draw();
  void init();
  void clear();
  void update();
};
