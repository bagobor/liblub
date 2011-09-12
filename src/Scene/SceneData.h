/*
 * SceneData.h
 *
 *  Created on: Mar 4, 2011
 *      Author: bmonkey
 */

#pragma once

#include "common/Singleton.h"

#include <string>
#include <QMap>
#include "Material/ShaderProgram.h"
#include "Material/Texture.h"
#include "Material/Material.h"
#include "Scene/Camera.h"
#include "Scene/Light.h"
#include "Mesh/Mesh.h"
#include "Material/UniformBuffer.h"

using std::string;

class SceneData : public Singleton<SceneData> {
public:
  string name;
  QVector3D backgroundColor;
  unsigned width, height;

  QMap<string, ShaderProgram*> shaderPrograms;
  QMap<string, Texture*> textures;
  QMap<string, Material*> materials;
  QMap<string, Mesh*> meshes;
  QMap<string, Camera*> cameras;
  QMap<string, Light*> lights;

  SceneData();
  virtual ~SceneData();
  void setBackgroundColor(const QVector3D backgroundColor);

  void addProgram(string & name, ShaderProgram * program);
  ShaderProgram* getProgram(const string & name);

  Material* getMaterial(const string & name);

  void addLight(const string & name, Light * light);
  Light* getLight(const string & name);
  Texture* getTexture(const string & name);
  Texture* getTexture(const string & name, const string & as);

  void setResolution(unsigned width, unsigned height);

  QSize getResolution();

  Camera * getCurrentCamera();
  Light * getShadowLight();
  void setShadowLight(Light * light);
  Light * getMoveLight();

  void setCurrentCamera(Camera * camera);
  void addCamera(Camera * camera);

private:
  Camera *currentCamera;
  Light *shadowLight, *moveLight;
};

