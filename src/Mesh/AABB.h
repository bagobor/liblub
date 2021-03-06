/*
 * AABB.h
 *
 *  Created on: Mar 5, 2011
 *      Author: bmonkey
 */

#pragma once

#include <QVector3D>

class Mesh;

class AABB {
public:
  AABB();
  virtual ~AABB();
  const QVector3D getCenter();

  void draw();
  void createMesh();

  void update(const QVector3D& position);
  void update(float x, float y, float z);
  Mesh * mesh;
  QVector3D min;
  QVector3D max;
  QVector3D center;
};
