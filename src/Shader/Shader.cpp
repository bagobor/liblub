/*
 * Copyright © 2010 Lubosz Sarnecki
 * Shader.cpp
 *
 *  Created on: Mar 22, 2010
 */

#include "Shader/Shader.h"

#include <QtCore>
#include <string>
#include <vector>
#include <fstream>
#include "System/Logger.h"
#include "System/Config.h"
#include "System/TemplateEngine.h"
#include "Renderer/OpenGL.h"

#include <fstream>
#include <streambuf>

using std::ifstream;
using std::istreambuf_iterator;

Shader::Shader(const string & fileName, GLenum type) {
  LogDebug << "Creating Shader" << fileName;
  this->fileName = fileName;
  this->type = type;

  shaderSource = "";

  defines = vector<string>();

  loadTemplate();
  compile();
}

Shader::~Shader() {
  glDeleteShader(handle);
}

void Shader::loadTemplate() {
  shaderSource = TemplateEngine::Instance().render(fileName).toStdString();
  handle = glCreateShader(type);
  /* Set rendered template string as source */
  const GLchar *source = shaderSource.c_str();
  glShaderSource(handle, 1,  &source, NULL);
}

void Shader::compile() {
  LogDebug << "Compiling Shader#" << handle << "...";
  glCompileShader(handle);
  printShaderInfoLog(handle);
  glError;
}

string Shader::readFile(string filePath) {
    QFile file(QString::fromStdString(filePath));
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         LogError << "Can not open File." << filePath;
     QString source = file.readAll();

     return source.toStdString();
}

void Shader::printShaderInfoLog(GLuint shader) {
  int infologLen = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
  if (infologLen > 1) {
    GLchar * infoLog = new GLchar[infologLen];
    if (infoLog == NULL) {
      LogError << "Could not allocate InfoLog buffer";
    }
    int charsWritten = 0;
    glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
    string shaderlog = infoLog;
    delete[] infoLog;
    LogError << "Shader Log"<< shaderlog;
  } else {
    LogDebug << "Success";
  }
}

GLuint Shader::getHandle() const {
  return handle;
}
