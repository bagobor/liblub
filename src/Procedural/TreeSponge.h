/*
 * TreeSponge.h
 *
 *  Created on: Sep 11, 2011
 *      Author: bmonkey
 */

#ifndef TREESPONGE_H_
#define TREESPONGE_H_

#include "Scene/Node.h"
#include <vector>
#include <QtCore>

const vector<QVector3D> translations = {
        // TOP
        QVector3D(0, 1, 1), QVector3D(-1, 1, 0),
        QVector3D(0, 1, -1), QVector3D(1, 1, 0),
        QVector3D(1, 1, 1), QVector3D(1, 1, -1),
        QVector3D(-1, 1, 1), QVector3D(-1, 1, -1),

        // MIDDLE
        QVector3D(1, 0, 1), QVector3D(1, 0, -1),
        QVector3D(-1, 0, 1), QVector3D(-1, 0, -1),

        // BOTTOM
        QVector3D(0, -1, 1), QVector3D(0, -1, -1),
        QVector3D(1, -1, 0), QVector3D(-1, -1, 0),
        QVector3D(1, -1, 1), QVector3D(1, -1, -1),
        QVector3D(-1, -1, 1), QVector3D(-1, -1, -1)
};

class TreeSponge : public Node{
public:
DirectionNode * viewPoint;
QMatrix4x4 viewProjection;

//    vector<QVector3D> translations;
    unsigned maxRecursion, minRecursion;
    TreeSponge(unsigned recursion, QList<string>& attributes, ShaderProgram *shader);
    virtual ~TreeSponge();
    void makeSponge(unsigned recursion, const QVector3D& parentPosition, float size);
    void draw(ShaderProgram * shader);
    static bool isNotCulled(const QMatrix4x4& mvp);
    bool endRecursionAdaptive(unsigned recursion, const QVector3D & cubePosition, float size);

    void drawAllChildren(unsigned recursion, const QVector3D& parentPosition, float size);
    void drawAllChildrenSorted(unsigned recursion, const QVector3D& parentPosition, float size);
};
#endif /* TREESPONGE_H_ */
