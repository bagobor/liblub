/*
 * InstancedSponge.cpp
 *
 *  Created on: Sep 11, 2011
 *      Author: bmonkey
 */

#include "InstancedSponge.h"
#include "Load/MeshLoader.h"
#include "Shader/ShaderProgram.h"

    InstancedSponge::InstancedSponge(unsigned recursion, QList<string>& attributes) {
        bufferCount = 1;
        makeSponge(recursion, {0, 0, 0}, 1.0f);
        setMesh(MeshLoader::load(attributes, "cube.obj"));
        calculateBufferSize();
        setCastShadows(false);
    }

    void InstancedSponge::makeSponge(
            unsigned recursion, const vector<float> & position, float size) {
      if (recursion == 0) {
        addCube(position, size);
      } else {
        recursion-=1;
        size/=3.0f;
        float trans = size*2;

        // TOP
        makeSponge(recursion,
                {position[0], position[1]+trans, position[2]+trans}, size);

        makeSponge(recursion,
                {position[0]-trans, position[1]+trans, position[2]}, size);
        makeSponge(recursion,
                {position[0], position[1]+trans, position[2]-trans}, size);
        makeSponge(recursion,
                {position[0]+trans, position[1]+trans, position[2]}, size);


        makeSponge(recursion,
                {position[0]+trans, position[1]+trans, position[2]+trans},
                size);
        makeSponge(recursion,
                {position[0]+trans, position[1]+trans, position[2]-trans},
                size);

        makeSponge(recursion,
                {position[0]-trans, position[1]+trans, position[2]+trans},
                size);
        makeSponge(recursion,
                {position[0]-trans, position[1]+trans, position[2]-trans},
                size);

        // MIDDLE
        makeSponge(recursion,
                {position[0]+trans, position[1], position[2]+trans}, size);
        makeSponge(recursion,
                {position[0]+trans, position[1], position[2]-trans}, size);

        makeSponge(recursion,
                {position[0]-trans, position[1], position[2]+trans}, size);
        makeSponge(recursion,
                {position[0]-trans, position[1], position[2]-trans}, size);

        // BOTTOM
        makeSponge(recursion,
                {position[0], position[1]-trans, position[2]+trans}, size);
        makeSponge(recursion,
                {position[0], position[1]-trans, position[2]-trans}, size);

        makeSponge(recursion,
                {position[0]+trans, position[1]-trans, position[2]}, size);
        makeSponge(recursion,
                {position[0]-trans, position[1]-trans, position[2]}, size);

        makeSponge(recursion,
                {position[0]+trans, position[1]-trans, position[2]+trans},
                size);
        makeSponge(recursion,
                {position[0]+trans, position[1]-trans, position[2]-trans},
                size);

        makeSponge(recursion,
                {position[0]-trans, position[1]-trans, position[2]+trans},
                size);
        makeSponge(recursion,
                {position[0]-trans, position[1]-trans, position[2]-trans},
                size);
      }
    }

    void InstancedSponge::addCube(const vector<float> & position, float size) {
//        LogDebug << "Making Cube" << size;
        positions.push_back(QVector4D(position[0] / size, position[1] / size, position[2] / size,1));
    }

    void InstancedSponge::draw(ShaderProgram * shader) {
        shader->activateAndBindTextures();
        foreach (UniformBuffer * buffer, positionBuffers){
                    buffer->bind();
                    shader->bindUniformBuffer("positions", 0, buffer->getHandle());
                    getMesh()->draw(positionBufferDataSize);
        }
    }

    void InstancedSponge::initBuffers(ShaderProgram * shader) {
        this->shader = shader;
        if(positions.size() <= 4096) {
            positionBuffers.push_back(initPositionBuffer(&positions));
        } else {
            for(unsigned currentBuffer = 0; currentBuffer < bufferCount; currentBuffer++){
                vector<QVector4D> * foo = new vector<QVector4D>();
                for(int currentPos = 0; currentPos < positionBufferDataSize; currentPos++){
                    foo->push_back(positions.back());
                    positions.pop_back();
                }
                positionBuffers.push_back(initPositionBuffer(foo));
            }
        }
    }

    UniformBuffer * InstancedSponge::initPositionBuffer(vector<QVector4D> * positionBufferData) {
          UniformBuffer * positionBuffer = new UniformBuffer();
          positionBuffer->bind();

          GLuint uniBlockIndex = glGetUniformBlockIndex(
                  shader->getHandle(), "positions");

          GLint positionBufferSize;
          glGetActiveUniformBlockiv(shader->getHandle(),
                  uniBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &positionBufferSize);

//          LogDebug << "Position Uniform Buffer Size" << positionBufferSize;
//          LogDebug << "Position Array Size" << positionBufferData->size();

          positionBuffer->write(positionBufferData->data(), positionBufferSize);
          shader->bindUniformBuffer("positions", 0,
                  positionBuffer->getHandle());
          glError;
          return positionBuffer;
      }

    void InstancedSponge::calculateBufferSize() {
           if(positions.size() <= 4096) {
               positionBufferDataSize = positions.size();
           } else {
               bufferCount = (positions.size() / 4096) + 1;
               positionBufferDataSize = positions.size() / bufferCount;
           }

           LogDebug << "Will create" << positions.size() << "cubes with" << bufferCount << "buffers (x "<< positionBufferDataSize << ")";
    }
