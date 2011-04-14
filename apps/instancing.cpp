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
#include <string>
#include <QApplication>
#include "System/Application.h"
#include "System/GUI.h"
#include "Scene/SceneLoader.h"
#include "Scene/SceneData.h"
#include "System/Logger.h"
#include "System/Timer.h"
#include "Scene/Node.h"

class LoadApp: public Application {
 public:

  Material * material;
  Node * node;
  explicit LoadApp() {
  }

  ~LoadApp() {}

  void scene() {
    QList<string> attributes;
    attributes.push_back("color");
    attributes.push_back("normal");
    attributes.push_back("uv");

    material = new Simple("Atmo/GroundFromAtmosphere",attributes);
    Mesh * cube = Geometry::makeCube();
  }
  void renderFrame(){
    node->setView(viewPoint);
    setShadowCoords(node, viewPoint);
    SceneData::Instance().getShadowLight()->bindShaderUpdate(node->getMaterial()->getShaderProgram());
    node->draw();
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  LoadApp(argv[1]).run();
}
