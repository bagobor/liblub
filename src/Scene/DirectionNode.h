/*
 * Copyright © 2010 Lubosz Sarnecki
 * DirectionNode.h
 *
 *  Created on: Oct 5, 2010
 */

#pragma once

#include <QtCore>
#include "Scene/Node.h"

const QVector3D up(0, 1, 0);

class DirectionNode : public Node{
public:
  DirectionNode();
  virtual ~DirectionNode();

  // View Params
  qreal aspect;
  qreal fov;
  qreal nearClip;
  qreal farClip;

  QMatrix4x4 viewMatrix, projectionMatrix;

  QVector3D sideDirection;

  QMatrix4x4 getView() const;
  QMatrix4x4 getViewNoTranslation();
  QMatrix4x4 getProjection() const;

  void setAspect(const qreal& aspect);

  void setFov(const qreal &fov);
  void setClipping(const qreal &nearClip, const qreal &farClip);

  void forwardDirection(qreal distance);
  void backwardDirection(qreal distance);
  void leftDirection(qreal distance);
  void rightDirection(qreal distance);

  void leftWorld(qreal distance);
  void rightWorld(qreal distance);
  void upWorld(qreal distance);
  void downWorld(qreal distance);
  void forwardWorld(qreal distance);
  void backWorld(qreal distance);

  void updatePerspective();
  void updateView();

  virtual void update() = 0;

  void updateSideDirection();
};
