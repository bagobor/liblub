/*
 Copyright © 2010 Lubosz Sarnecki

 This file is part of liblub.

 liblub is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 liblub is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with liblub.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Mesh/FractalMesh.h"
#include "Scene/Scene.h"
#include "System/Demo.h"

class JuliaDemo: public Demo {
public:

    Mesh * mesh;
    ShaderProgram * shader;
    Node * node;
    FractalMesh * fractal;
    float phase;
    QList<string> attributes;

    JuliaDemo() ;
    ~JuliaDemo();

    Mesh * plane(const QList<string> & attributes, unsigned resolution, float density);
    Mesh * sinePlane(const QList<string> & attributes, unsigned resolution, float density, float phase);

    void init();
    void draw();
};

