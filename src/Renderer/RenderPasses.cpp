/*
 * Copyright © 2010 Lubosz Sarnecki
 * RenderPasses.cpp
 *
 *  Created on: Oct 5, 2010
 */

#include "Window/MediaLayer.h"
#include "Scene/Camera.h"
#include "Scene/SceneData.h"
#include "Material/Materials.h"

LightViewDepthPass::LightViewDepthPass(FrameBuffer * fbo) {
    this->fbo = fbo;
    targetTexture = TextureFactory::Instance().depthTexture(fbo->width,
            fbo->height, "shadowMap");
    fbo->attachTexture(GL_DEPTH_ATTACHMENT, targetTexture);
    fbo->disableColorBuffer();

    material = new Minimal();
}

void LightViewDepthPass::prepare() {
    fbo->bind();

    glPolygonOffset(2.0, 0.0);
    RenderEngine::Instance().clear();

    // In the case we render the shadowmap to a higher resolution,
    // the viewport must be modified accordingly.
    fbo->updateRenderView();
    material->activate();
}

void LightViewDepthPass::draw() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
    SceneGraph::Instance().drawCasters(material);
}

void LightViewDepthPass::cleanUp() {
    fbo->unBind();
    glPolygonOffset(0.0, 0.0);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
}

FilterPass::FilterPass(FrameBuffer * fbo) {
    this->fbo = fbo;
    targetTexture = TextureFactory::Instance().depthTexture(fbo->width,
            fbo->height, "shadowMap");
    fbo->attachTexture(GL_DEPTH_ATTACHMENT, targetTexture);
    fbo->disableColorBuffer();

    material = new Minimal();
}

void FilterPass::prepare() {
    fbo->bind();

    RenderEngine::Instance().clear();

    // In the case we render the shadowmap to a higher resolution,
    // the viewport must be modified accordingly.
    fbo->updateRenderView();
    SceneGraph::Instance().drawNodes(SceneData::Instance().getCurrentCamera());
    fbo->unBind();

    glPolygonOffset(20.0, 0.0);
    material->activate();

}

void FilterPass::draw(Material * material) {
    fbo->draw(material);
}

void FilterPass::cleanUp() {
    fbo->unBind();
    glPolygonOffset(0.0, 0.0);
}

LightTogglePass::LightTogglePass() {
}

void LightTogglePass::prepare() {
    RenderEngine::Instance().clear();
}

void LightTogglePass::draw() {
    glViewport(0, 0, MediaLayer::Instance().width,
            MediaLayer::Instance().height);
    if (RenderEngine::Instance().lightView) {
        SceneGraph::Instance().drawNodes(SceneData::Instance().getShadowLight());
    } else {
        SceneGraph::Instance().drawNodes(SceneData::Instance().getCurrentCamera());
    }
}

void LightTogglePass::cleanUp() {
}
