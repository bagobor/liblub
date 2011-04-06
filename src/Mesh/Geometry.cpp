/*
 * Copyright © 2010 Lubosz Sarnecki
 * Geomerty.cpp
 *
 *  Created on: Mar 24, 2010
 */
#include <math.h>
#include <vector>
#include "Mesh/Geometry.h"
#include "common/Qt3D.h"
#include "System/Logger.h"

Mesh * Geometry::makePlane(const QRectF &plane) {
    vector<GLfloat> vertices = {
        (float)plane.left(), (float)plane.top(), -1.0,
        (float)plane.right(), (float)plane.top(), -1.0,
        (float)plane.right(), (float)plane.bottom(), -1.0,
        (float)plane.left(), (float)plane.bottom(), -1.0
    };
    vector<GLfloat> uvCoords = {
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
    };

    vector<GLfloat> normals = {
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0
    };

    vector<GLuint> indicies = { 0, 1, 3, 3, 1, 2 };

    Mesh * mesh = new Mesh();
    mesh->init();
    mesh->addBuffer(vertices, 3, "in_Vertex");
    mesh->addBuffer(normals, 3, "in_Normal");
//    mesh->addBuffer(normals, 3, "in_Tangent");
//    mesh->addBuffer(normals, 3, "in_Biangent");
    mesh->addBuffer(uvCoords, 2, "in_Uv");
    mesh->addElementBuffer(indicies);
    mesh->setDrawType(GL_TRIANGLES);
    glError;
    return mesh;
}

Mesh * Geometry::makePlaneTess() {
    vector<GLfloat> vertices = {
            1, 1, 0,
            1, -1, 0,
            -1, -1, 0,
            -1, 1, 0
    };

    vector<GLuint> indicies = { 0, 1, 2, 0, 2, 3 };
    Mesh * mesh = new Mesh();
    mesh->init();
    mesh->addBuffer(vertices, 3, "in_Vertex");
    mesh->addElementBuffer(indicies);
    mesh->setDrawType(GL_PATCHES);
    return mesh;
}

Mesh * Geometry::makeTetrahedron() {
    vector<GLfloat> vertices = {
            1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            -1.0, 1.0, -1.0,
            1.0, -1.0, -1.0
    };

    vector<GLfloat> vertexColors = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0
    };

    vector<GLfloat> uvCoords = {
            1.0, 0.0,
            0.0, 1.0,
            0.0, 0.0,
            1.0, 1.0
    };

    vector<GLfloat> normals = {
            1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            -1.0, 1.0, -1.0,
            1.0, -1.0, -1.0 };

    vector<GLuint> indicies = { 0, 1, 2, 3, 0, 1 };

    Mesh * mesh = new Mesh();
    mesh->init();
    mesh->addBuffer(vertices, 3, "in_Vertex");
    mesh->addBuffer(vertexColors, 3, "in_Color");
    mesh->addBuffer(normals, 3, "in_Normal");
    mesh->addBuffer(uvCoords, 2, "in_Uv");

    mesh->addElementBuffer(indicies);
    return mesh;
}

Mesh * Geometry::makeCube() {
    vector<GLfloat> vertices = {
        1.0, -1.0, -1.0,
        1.0, -1.0, 1.0,
        -1.0, -1.0, 1.0,
        -1.0, -1.0, -1.0,
        1.0, 1.0, -1.0,
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        -1.0, 1.0, -1.0
    };

    vector<GLfloat> vertexColors = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0
    };

    vector<GLfloat> uvCoords = {
        1.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
    };

    vector<GLuint> indicies = {
            4, 0, 3, 4, 3, 7,
            1, 5, 2, 5, 6, 2,
            2, 6, 7, 2, 7, 3,
            0, 4, 1, 4, 5, 1,
            4, 7, 5, 7, 6, 5,
            0, 1, 2, 0, 2, 3
    };

    Mesh * mesh = new Mesh();
    mesh->init();
    mesh->addBuffer(vertices, 3, "in_Vertex");
    mesh->addBuffer(vertices, 3, "in_Color");
    mesh->addBuffer(uvCoords, 2, "in_Uv");
    mesh->addBuffer(vertices, 3, "in_Normal");
    mesh->addElementBuffer(indicies);
    return mesh;
}

float Geometry::randomize(float density, float randomness) {
    unsigned seed;
    float randomValue = 1 / static_cast<float>((rand_r(&seed) % 20) + 1);

    return density + (density * randomValue * randomness);
}

Mesh * Geometry::makeStars(vector<float> & resolution, float density,
        float randomness, float colorIntensity) {
    vector<GLfloat> vertices, colors;
    vector<GLuint> indicies;

    unsigned i = 0;

    srand(time(NULL));

    for (float x = 0; x < resolution.at(0);
            x += randomize(density, randomness)) {
        for (float y = 0; y < resolution.at(1); y += randomize(density,
                randomness)) {
            for (float z = 0; z < resolution.at(2); z += randomize(density,
                    randomness)) {
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                colors.push_back(static_cast<float>(
                        static_cast<int>(x * colorIntensity) % 255) / 256);
                colors.push_back(static_cast<float>(
                        static_cast<int>(y * colorIntensity) % 255) / 256);
                colors.push_back(static_cast<float>(
                        static_cast<int>(z * colorIntensity) % 255) / 256);

                indicies.push_back(i);

                i++;
            }
        }
    }
    Logger::Instance().message << i << " Generated Stars";
    Logger::Instance().log("MESSAGE", "makeStars");

    Mesh * mesh = new Mesh();
    mesh->init();
    mesh->addBuffer(vertices, 3, "in_Vertex");
    mesh->addBuffer(colors, 3, "in_Color");
    mesh->addElementBuffer(indicies);
    return mesh;
}

Mesh * Geometry::makeSpiral(int resolution) {
    vector<GLfloat> vertices, colors;
    vector<GLuint> indicies;

    QVector3D point = QVector3D(1, 0, 0);
    QMatrix4x4 rotation = QMatrix4x4();
    rotation.rotate(0.5, 0.0, 1.0, 0.0);

    QMatrix4x4 rotation2 = QMatrix4x4();
    rotation2.rotate(0.5, 0.0, 0.0, 1.0);

    int i = 1;

    srand(time(NULL));
    for (; i < resolution; i++) {
        QVector3D tempPoint = point.normalized();
        point += (tempPoint / 20.0);

        point = rotation * point;

        QVector3D newPoint = point;
        for (int j = 0; j < 100; j++) {
            newPoint = rotation2 * newPoint;

            QVector3D tempPoint2 = newPoint.normalized();
            newPoint += (tempPoint2 / 20.0);

            vertices.push_back(newPoint.x());
            vertices.push_back(newPoint.y());
            vertices.push_back(newPoint.z());

            colors.push_back(1.0 - (static_cast<float>(
                    static_cast<int>(newPoint.x()) % 255) / 256));
            colors.push_back(1.0 - (static_cast<float>(
                    static_cast<int>(newPoint.y()) % 255) / 256));
            colors.push_back(1.0 - (static_cast<float>(
                    static_cast<int>(newPoint.z()) % 255) / 256));

            indicies.push_back(i);
            i++;
        }
    }

    Logger::Instance().message << i << " Generated Points";
    Logger::Instance().log("MESSAGE", "makeSpiral");

    Mesh * mesh = new Mesh();
    mesh->init();
    mesh->addBuffer(vertices, 3, "in_Vertex");
    mesh->addBuffer(colors, 3, "in_Color");
    mesh->addElementBuffer(indicies);
    mesh->setDrawType(GL_POINTS);
    return mesh;
}

Mesh * Geometry::gluSphere(GLdouble radius, GLint slices, GLint stacks) {

  Mesh *sphere = new Mesh();
  Mesh * middleStrip = new Mesh();
  Mesh * bottomFan = new Mesh();
  Mesh * topFan = new Mesh();
  bool hasNormals = true;
  bool smoothNormals = true;
  bool drawPoints = false;
  bool drawLines = false;
  bool orientationOutside = true;
  bool useTextureCoords = true;
  GLenum drawStyle = GL_FILL;
#define CACHE_SIZE  240
  GLint i, j;
  GLfloat sinCache1a[CACHE_SIZE];
  GLfloat cosCache1a[CACHE_SIZE];
  GLfloat sinCache2a[CACHE_SIZE];
  GLfloat cosCache2a[CACHE_SIZE];
  GLfloat sinCache3a[CACHE_SIZE];
  GLfloat cosCache3a[CACHE_SIZE];
  GLfloat sinCache1b[CACHE_SIZE];
  GLfloat cosCache1b[CACHE_SIZE];
  GLfloat sinCache2b[CACHE_SIZE];
  GLfloat cosCache2b[CACHE_SIZE];
  GLfloat sinCache3b[CACHE_SIZE];
  GLfloat cosCache3b[CACHE_SIZE];
  GLfloat angle;
  GLfloat zLow, zHigh;
  GLfloat sintemp1 = 0.0, sintemp2 = 0.0, sintemp3 = 0.0, sintemp4 = 0.0;
//    GLfloat costemp1 = 0.0, costemp2 = 0.0;
  GLfloat costemp3 = 0.0, costemp4 = 0.0;
  GLboolean needCache2, needCache3;
  GLint start, finish;

  if (slices >= CACHE_SIZE)
    slices = CACHE_SIZE - 1;
  if (stacks >= CACHE_SIZE)
    stacks = CACHE_SIZE - 1;
//    if (slices < 2 || stacks < 1 || radius < 0.0) {
//      gluQuadricError(qobj, GL_INVALID_VALUE);
//      return;
//    }

  /* Cache is the vertex locations cache */
  /* Cache2 is the various normals at the vertices themselves */
  /* Cache3 is the various normals for the faces */
  needCache2 = needCache3 = GL_FALSE;

  if (smoothNormals) {
    needCache2 = GL_TRUE;
  } else {
    if (!drawPoints) {
      needCache3 = GL_TRUE;
    }
    if (drawLines) {
      needCache2 = GL_TRUE;
    }
  }

  for (i = 0; i < slices; i++) {
    angle = 2 * M_PI * i / slices;
    sinCache1a[i] = sin(angle);
    cosCache1a[i] = cos(angle);
    if (needCache2) {
      sinCache2a[i] = sinCache1a[i];
      cosCache2a[i] = cosCache1a[i];
    }
  }

  for (j = 0; j <= stacks; j++) {
    angle = M_PI * j / stacks;
    if (needCache2) {
      if (orientationOutside) {
        sinCache2b[j] = sin(angle);
        cosCache2b[j] = cos(angle);
      } else {
        sinCache2b[j] = -sin(angle);
        cosCache2b[j] = -cos(angle);
      }
    }
    sinCache1b[j] = radius * sin(angle);
    cosCache1b[j] = radius * cos(angle);
  }
  /* Make sure it comes to a point */
  sinCache1b[0] = 0;
  sinCache1b[stacks] = 0;

  if (needCache3) {
    for (i = 0; i < slices; i++) {
      angle = 2 * M_PI * (i - 0.5) / slices;
      sinCache3a[i] = sin(angle);
      cosCache3a[i] = cos(angle);
    }
    for (j = 0; j <= stacks; j++) {
      angle = M_PI * (j - 0.5) / stacks;
      if (orientationOutside) {
        sinCache3b[j] = sin(angle);
        cosCache3b[j] = cos(angle);
      } else {
        sinCache3b[j] = -sin(angle);
        cosCache3b[j] = -cos(angle);
      }
    }
  }

  sinCache1a[slices] = sinCache1a[0];
  cosCache1a[slices] = cosCache1a[0];
  if (needCache2) {
    sinCache2a[slices] = sinCache2a[0];
    cosCache2a[slices] = cosCache2a[0];
  }
  if (needCache3) {
    sinCache3a[slices] = sinCache3a[0];
    cosCache3a[slices] = cosCache3a[0];
  }

  switch (drawStyle) {
  case GL_FILL:
    /* Do ends of sphere as TRIANGLE_FAN's (if not texturing)
     ** We don't do it when texturing because we need to respecify the
     ** texture coordinates of the apex for every adjacent vertex (because
     ** it isn't a constant for that point)
     */
    if (!useTextureCoords) {
      start = 1;
      finish = stacks - 1;

      /* Low end first (j == 0 iteration) */
      sintemp2 = sinCache1b[1];
      zHigh = cosCache1b[1];

      if(smoothNormals){
        sintemp3 = sinCache2b[1];
        costemp3 = cosCache2b[1];
        topFan->addNormal(sinCache2a[0] * sinCache2b[0], cosCache2a[0]
            * sinCache2b[0], cosCache2b[0]);
      }else{
        sintemp3 = sinCache3b[1];
        costemp3 = cosCache3b[1];
      }


      //glBegin(GL_TRIANGLE_FAN);
      topFan->addPosition(0.0, 0.0, radius);
      if (orientationOutside) {
        for (i = slices; i >= 0; i--) {
          if(smoothNormals){
            topFan->addNormal(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3,
                costemp3);
          }else{
            if (i != slices) {
              topFan->addNormal(sinCache3a[i + 1] * sintemp3, cosCache3a[i + 1]
                  * sintemp3, costemp3);
            }
          }
          topFan->addPosition(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i],
              zHigh);
        }
      } else {
//          for (i = 0; i <= slices; i++) {
//            if (smoothNormals) {
//              addNormal(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3,
//                  costemp3);
//            } else {
//              addNormal(sinCache3a[i] * sintemp3, cosCache3a[i] * sintemp3,
//                  costemp3);
//            }
//            addPosition(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i],
//                zHigh);
//          }
      }
      //glEnd();

      /* High end next (j == stacks-1 iteration) */
      sintemp2 = sinCache1b[stacks - 1];
      zHigh = cosCache1b[stacks - 1];

      if (smoothNormals) {
        sintemp3 = sinCache2b[stacks - 1];
        costemp3 = cosCache2b[stacks - 1];
        bottomFan->addNormal(sinCache2a[stacks] * sinCache2b[stacks],
            cosCache2a[stacks] * sinCache2b[stacks], cosCache2b[stacks]);
      } else {
        sintemp3 = sinCache3b[stacks];
        costemp3 = cosCache3b[stacks];
      }

      //glBegin(GL_TRIANGLE_FAN);
      bottomFan->addPosition(0.0, 0.0, -radius);
      if (orientationOutside) {
        for (i = 0; i <= slices; i++) {
          if (smoothNormals) {
            bottomFan->addNormal(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3,
                costemp3);
          } else {
            bottomFan->addNormal(sinCache3a[i] * sintemp3, cosCache3a[i] * sintemp3,
                costemp3);
          }
          bottomFan->addPosition(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i],
              zHigh);
        }
      } else {
//          for (i = slices; i >= 0; i--) {
//            if (smoothNormals) {
//              addNormal(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3,
//                  costemp3);
//            } else {
//              if (i != slices) {
//                addNormal(sinCache3a[i + 1] * sintemp3, cosCache3a[i + 1]
//                    * sintemp3, costemp3);
//              }
//            }
//            addPosition(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i],
//                zHigh);
//          }
      }
      //glEnd();
    } else {
      start = 0;
      finish = stacks;
    }
    for (j = start; j < finish; j++) {
      zLow = cosCache1b[j];
      zHigh = cosCache1b[j + 1];
      sintemp1 = sinCache1b[j];
      sintemp2 = sinCache1b[j + 1];


      if (smoothNormals) {
        if (orientationOutside) {
          sintemp3 = sinCache2b[j + 1];
          costemp3 = cosCache2b[j + 1];
          sintemp4 = sinCache2b[j];
          costemp4 = cosCache2b[j];
        } else {
          sintemp3 = sinCache2b[j];
          costemp3 = cosCache2b[j];
          sintemp4 = sinCache2b[j + 1];
          costemp4 = cosCache2b[j + 1];
        }
      } else {
        sintemp4 = sinCache3b[j + 1];
        costemp4 = cosCache3b[j + 1];
      }

      //glBegin(GL_QUAD_STRIP);
      for (i = 0; i <= slices; i++) {
          if (smoothNormals)
            middleStrip->addNormal(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3,
                costemp3);
        if (orientationOutside) {
          if (useTextureCoords) {
            middleStrip->addUv(1 - (float) i / slices, 1 - (float) (j + 1) / stacks);
          }
          middleStrip->addPosition(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i],
              zHigh);
        } else {
//            if (useTextureCoords) {
//              glTexCoord2f(1 - (float) i / slices, 1 - (float) j / stacks);
//            }
//            addPosition(sintemp1 * sinCache1a[i], sintemp1 * cosCache1a[i], zLow);
        }
        if (hasNormals && smoothNormals) {
          middleStrip->addNormal(sinCache2a[i] * sintemp4, cosCache2a[i] * sintemp4,
              costemp4);
//            middleStrip->addNormal(sinCache3a[i] * sintemp4, cosCache3a[i] * sintemp4,
//                costemp4);
        }
        if (orientationOutside) {
          if (useTextureCoords) {
            middleStrip->addUv(1 - (float) i / slices, 1 - (float) j / stacks);
          }
          middleStrip->addPosition(sintemp1 * sinCache1a[i], sintemp1 * cosCache1a[i], zLow);
        } else {
//            if (useTextureCoords) {
//              glTexCoord2f(1 - (float) i / slices, 1 - (float) (j + 1) / stacks);
//            }
//            addPosition(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i],
//                zHigh);
        }
      }
      //glEnd();
    }
    break;
//    case GL_POINT:
//      //glBegin(GL_POINTS);
//      for (j = 0; j <= stacks; j++) {
//        sintemp1 = sinCache1b[j];
//        costemp1 = cosCache1b[j];
//        if (hasNormals && smoothNormals) {
//          sintemp2 = sinCache2b[j];
//          costemp2 = cosCache2b[j];
//        }
//
//        for (i = 0; i < slices; i++) {
//          if (hasNormals && smoothNormals) {
//            addNormal(sinCache2a[i] * sintemp2, cosCache2a[i] * sintemp2,
//                costemp2);
//          }
//
//          zLow = j * radius / stacks;
//
//          if (useTextureCoords) {
//            glTexCoord2f(1 - (float) i / slices, 1 - (float) j / stacks);
//          }
//          addPosition(sintemp1 * sinCache1a[i], sintemp1 * cosCache1a[i],
//              costemp1);
//        }
//      }
//      //glEnd();
//      break;
//    case GL_LINE:
//      for (j = 1; j < stacks; j++) {
//        sintemp1 = sinCache1b[j];
//        costemp1 = cosCache1b[j];
//        if (hasNormals && smoothNormals) {
//          sintemp2 = sinCache2b[j];
//          costemp2 = cosCache2b[j];
//        }
//
//        //glBegin(GL_LINE_STRIP);
//        for (i = 0; i <= slices; i++) {
//          if (hasNormals) {
//            if (smoothNormals) {
//            addNormal(sinCache2a[i] * sintemp2, cosCache2a[i] * sintemp2,
//                costemp2);
//            } else {
//            addNormal(sinCache3a[i] * sintemp2, cosCache3a[i] * sintemp2,
//                costemp2);
//            }
//          }
//          if (useTextureCoords) {
//            glTexCoord2f(1 - (float) i / slices, 1 - (float) j / stacks);
//          }
//          addPosition(sintemp1 * sinCache1a[i], sintemp1 * cosCache1a[i],
//              costemp1);
//        }
//        //glEnd();
//      }
//      for (i = 0; i < slices; i++) {
//        sintemp1 = sinCache1a[i];
//        costemp1 = cosCache1a[i];
//        if (hasNormals && smoothNormals) {
//          sintemp2 = sinCache2a[i];
//          costemp2 = cosCache2a[i];
//        }
//
//        //glBegin(GL_LINE_STRIP);
//        for (j = 0; j <= stacks; j++) {
//          if (hasNormals) {
//            if (smoothNormals) {
//            addNormal(sintemp2 * sinCache2b[j], costemp2 * sinCache2b[j],
//                cosCache2b[j]);
//            } else {
//            addNormal(sintemp2 * sinCache3b[j], costemp2 * sinCache3b[j],
//                cosCache3b[j]);
//            }
//          }
//
//          if (useTextureCoords) {
//            glTexCoord2f(1 - (float) i / slices, 1 - (float) j / stacks);
//          }
//          addPosition(sintemp1 * sinCache1b[j], costemp1 * sinCache1b[j],
//              cosCache1b[j]);
//        }
//        //glEnd();
//      }
//      break;
  default:
    break;
  }

  middleStrip->init();
  middleStrip->initPositions();
  middleStrip->initNormals();
  middleStrip->initUv();
  middleStrip->initIndex();
  middleStrip->setDrawType(GL_TRIANGLE_STRIP);

  topFan->init();
  topFan->initPositions();
  topFan->initNormals();
  topFan->initIndex();
  topFan->setDrawType(GL_TRIANGLE_FAN);

  bottomFan->init();
  bottomFan->initPositions();
  bottomFan->initNormals();
  bottomFan->initIndex();
  bottomFan->setDrawType(GL_TRIANGLE_FAN);

  sphere->addSubMesh(middleStrip);
  sphere->addSubMesh(topFan);
  sphere->addSubMesh(bottomFan);

  return sphere;

}
