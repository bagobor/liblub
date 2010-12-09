/*
 * Mesh.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: bmonkey
 */

#include "RenderEngine.h"
#include "Logger.h"

Mesh::Mesh(){
	drawType = GL_POINTS;
	bufferCount = 0;
	indexSize = 0;

    /* Allocate and assign a Vertex Array Object to our handle */
    glGenVertexArrays(1, &vao);
    Logger::Instance().message << "Generating Vertex Array Object #"<< vao;
    Logger::Instance().log("DEBUG");

    /* Bind our Vertex Array Object as the current used object */
    glBindVertexArray(vao);

    /* Allocate and assign three Vertex Buffer Objects to our handle */
    glGenBuffers(maxBuffers, vbo);
    Logger::Instance().message << "Vertex Buffers #" << vbo;
    Logger::Instance().log("DEBUG");
}

Mesh::~Mesh() {
	for (int i = 0; i < bufferCount; i++){
		glDisableVertexAttribArray(i);
	}
    glDeleteBuffers(maxBuffers, vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::addBuffer(vector<GLfloat> content, unsigned size, string name){
    glError("Mesh::addBuffer",39);
	//RenderEngine::Instance().shaderProgram->bindAttrib(name);
	//RenderEngine::Instance().shaderProgram->bindAttribIfUnbound(name);

    /* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[bufferCount]);

	/* Copy the vertex data from tetrahedron to our buffer */
	/* 12 * sizeof(GLfloat) is the size of the tetrahedrom array, since it contains 12 GLfloat values */
	glBufferData(GL_ARRAY_BUFFER, content.size() * sizeof(GLfloat), content.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, content.size() * sizeof(GLfloat), content.data(), GL_STREAM_DRAW);

	/* Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex */
	glVertexAttribPointer((GLuint) bufferCount, size, GL_FLOAT, GL_FALSE, 0, 0);

	/* Enable attribute index 0 as being used */
	glEnableVertexAttribArray(bufferCount);
	//glVertexAttribDivisor(1,2);
    Logger::Instance().message << "Adding Vertex Buffer #" << bufferCount << " "<< name<< " Size:"<< content.size();
    Logger::Instance().log("DEBUG");
	/*
	BOOST_FOREACH(float value, content){
		cout << value << "\n";
	}
	*/
	bufferCount++;
    glError("Mesh::addBuffer",64);
}

void Mesh::addElementBuffer(vector<GLuint> content){

	indexSize = content.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[bufferCount]);
	glError("Mesh::addBuffer",71);
	/* Copy the index data from tetraindicies to our buffer
	 * 6 * sizeof(GLubyte) is the size of the index array, since it contains 6 GLbyte values */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, content.size() * sizeof(GLuint), content.data(),GL_STATIC_DRAW);
    Logger::Instance().message << "Adding Vertex Element Buffer #" << bufferCount << " Size:"<< content.size();
    Logger::Instance().log("DEBUG");
	bufferCount++;
    glError("Mesh::addElementBuffer",76);
}

void Mesh::setDrawType(GLint drawType){
	this->drawType = drawType;
}

void Mesh::draw(){
	/*
	unsigned vertCount = 3;
	GLuint glIndices[indices.size()];
	for (unsigned i = 0; i < indices.size(); i++){
		glIndices[i] = indices[i];
	}
	for (unsigned i = 0; i < (indexSize/3); i++){
		//glDrawElements(drawType, vertCount, GL_UNSIGNED_INT, &indices.data()[i*3]);
		glDrawElements(drawType, vertCount, GL_UNSIGNED_INT, &glIndices[i*3]);
		vertCount+=3;
	}
	*/
	//glDrawElementsInstanced(drawType, indexSize, GL_UNSIGNED_INT, 0,6);

	glBindVertexArray(vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[bufferCount]);
	glDrawElements(drawType, indexSize, GL_UNSIGNED_INT, 0);
}
