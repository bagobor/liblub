/*
 * Copyright © 2010 Lubosz Sarnecki
 * Node.h
 *
 *  Created on: Jun 28, 2010
 */

#pragma once

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "Scene/DirectionNode.h"


class Node {
 private:
	string name;
	QVector3D position;
	float size;
	Node * parent;
	QMatrix4x4 modelMatrix;
	Material * material;
	bool castShadows, receiveShadows;

 public:
	Node(
	        string name, const QVector3D& position,
	        float size, Mesh * mesh, Material * material
	);
	virtual ~Node();

	Mesh * mesh;
  bool getCastShadows() const;
  void setCastShadows(bool castShadows);
  bool getReceiveShadows() const;
  void setReceiveShadows(bool receiveShadows);
  void setSize(float size);
  void setMesh(Mesh *mesh);
  void setPosition(const QVector3D& position);
  void draw();
  void bindShaders(ShaderProgram * shaderProgram, DirectionNode * viewPoint);
  void bindShaders(DirectionNode * viewPoint);
  string getName() const;
  const QVector3D& getPosition();
  void setName(string name);
  Material *getMaterial() const;
  void setMaterial(Material *material);
  float getSize() const;
  void update();
};
