/*
 * SceneData.h
 *
 *  Created on: Mar 4, 2011
 *      Author: bmonkey
 */

#pragma once

#include "Common/Singleton.h"

#include <string>
#include <QMap>
#include "Shader/ShaderProgram.h"
#include "Texture/Texture.h"
#include "Scene/Material.h"
#include "Scene/Camera.h"
#include "Scene/Light.h"
#include "Mesh/Mesh.h"
#include "Shader/UniformBuffer.h"

using std::string;


class Scene : public Singleton<Scene> {
public:
  string name;
  QVector3D backgroundColor;
  unsigned width, height;

  QMap<string, Material*> materials;
  QMap<string, ShaderProgram*> shaders;
  QMap<string, Texture*> textures;
  QMap<string, Mesh*> meshes;
  QMap<string, Camera*> cameras;
  QMap<string, Light*> lights;

  Scene();
  virtual ~Scene();
  void setBackgroundColor(const QVector3D backgroundColor);

  void addShader(string & name, ShaderProgram * program);
  ShaderProgram* getShader(const string & name);

  void addLight(const string & name, Light * light);
  Light* getLight(const string & name);
  Texture* getTexture(const string & name);
  Texture* getTexture(const string & name, const string & as);

  void setResolution(unsigned width, unsigned height);

  QSize getResolution();

  Camera * getCurrentCamera();

  void setCurrentCamera(Camera * camera);
  void addCamera(Camera * camera);
  void addCamera(const QVector3D & pos, const QVector3D & dir);

  Light* getDefaultLight();

  struct LightSource {
    QVector4D position;
    QVector4D diffuse;
    QVector4D specular;
    QVector4D direction;
  };

  LightSource lightBufferData[10];
  UniformBuffer * lightBuffer;
  GLint lightBufferSize;
  void initLightBuffer(ShaderProgram * shader, const string& bufferName);

  void initSkyMaterial(const string& textureName);
  void initSkyShader(const string& textureName);
  void initSkyShaderSphere(const string& textureName);

private:
  Camera *currentCamera;
};

