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
#include "System/Logger.h"
#include "Material/Shaders.h"
#include "Material/Textures.h"
#include "Scene/SceneGraph.h"
#include "Renderer/RenderPasses.h"
#include "System/Application.h"
#include "Renderer/DeferredRenderer.h"
#include "Scene/Scene.h"
#include "Window/Qt/PassModel.h"
#include "Scene/BlenderLoader.h"

class NatureApp: public Application {
public:

    NatureApp(int argc, char *argv[]) :
        Application(argc, argv) {
    }

    ~NatureApp() {
    }

    void scene() {
        Scene::Instance().getCurrentCamera()->setPosition(QVector3D(-1.43765, 5.130675, -1.20157));
        Scene::Instance().getCurrentCamera()->setDirection(QVector3D(0.741701, -0.0836778, 0.66549));
        Scene::Instance().getCurrentCamera()->update();

        Texture* env = new CubeTextureFile("cubemaps/sky", "sky");

        BlenderLoader::Instance().load("nature.blend");
        DeferredRenderer::Instance().init();
    }
    void renderFrame() {
        DeferredRenderer::Instance().draw();
    }
};

int main(int argc, char *argv[]) {
    NatureApp(argc, argv).run();
}

