/*
 * Copyright © 2010 Lubosz Sarnecki
 * Light.cpp
 *
 *  Created on: Oct 1, 2010
 */

#include "Scene/Light.h"
#include "Scene/SceneGraph.h"
#include "Scene/SceneData.h"
#include "Scene/Camera.h"
#include "Material/Materials.h"
#include "Mesh/MeshFactory.h"
#include "System/Logger.h"

Light::Light(const QVector3D& position, const QVector3D & direction) {
  this->position = position;
  this->direction = direction;
  defaultDirection = direction;
  updatePerspective();
  update();
}

Light::~Light() {
    // TODO(bmonkey): Auto-generated destructor stub
}

void Light::setColor(QVector4D & color) {
    this->color = color;
}

void Light::bindShaderUpdate(ShaderProgram * shaderProgram) {
    QVector4D lightPositionView = SceneData::Instance().getCurrentCamera()->getView() * position;

    shaderProgram->setUniform(lightPositionView, "lightPositionView");
    shaderProgram->setUniform(position, "lightPosition");

    QVector3D directionView = SceneData::Instance().getCurrentCamera()->getView() * direction;
    shaderProgram->setUniform(directionView, "spotDirection");

    QVector3D spotDirectionView = SceneData::Instance().getCurrentCamera()->getViewNoTranslation()
            * direction;
    spotDirectionView.normalize();
    shaderProgram->setUniform(spotDirectionView, "spotDirectionView");
}

void Light::bindShaderUpdateLight(ShaderProgram * shaderProgram) {
    QVector4D lightPositionView = getView() * position;

    shaderProgram->setUniform(lightPositionView, "lightPositionView");

    QVector3D directionView = getView() * direction;
    shaderProgram->setUniform(directionView, "spotDirection");

    QVector3D spotDirectionView = getViewNoTranslation() * direction;
    spotDirectionView.normalize();
    shaderProgram->setUniform(spotDirectionView, "spotDirectionView");
}

void Light::bindShaderInit(ShaderProgram * shaderProgram) {
  //TODO: Hardcoded light stuff
    shaderProgram->setUniform(QVector4D(1.9, 1.9, 1.9, 1.0), "lightColor");

    GLuint program = shaderProgram->getReference();

    // attenuation
    glUniform1f(glGetUniformLocation(program, "constantAttenuation"), 0);
    // glUniform1f(glGetUniformLocation(program, "linearAttenuation"), .8);
    glUniform1f(glGetUniformLocation(program, "quadraticAttenuation"), .005);

    // spot
    glUniform1f(glGetUniformLocation(program, "spotOuterAngle"), 0.9);
    glUniform1f(glGetUniformLocation(program, "spotInnerAngle"), 0.8);
}

void Light::moveLeft() {
    position += QVector3D(-speed, 0, 0);
    update();
}

void Light::moveRight() {
    position += QVector3D(speed, 0, 0);
    update();
}

void Light::moveUp() {
    position += QVector3D(0, speed, 0);
    update();
}

void Light::moveDown() {
    position += QVector3D(0, -speed, 0);
    update();
}

void Light::moveForward() {
    position += QVector3D(0, 0, speed);
    update();
}

void Light::moveBack() {
    position += QVector3D(0, 0, -speed);
    update();
}

void Light::update() {
  //TODO: Multiple lights
    SceneGraph::Instance().setPosition("Light", position);
    Logger::Instance().message << position.x() << " " << position.y() << " "
            << position.z();
    Logger::Instance().log("DEBUG", "Light Position");
    updateView();
}
