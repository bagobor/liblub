
/*
 * MediaLayer.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: bmonkey
 */

#include <QtGui>
#include "QtWindow.h"
#include "QtInput.h"
#include "System/Logger.h"
#include "System/Timer.h"
#include "Scene/Scene.h"
#include "Window/Qt/QtInput.h"

QtWindow::QtWindow() {
  mainLayout = new QHBoxLayout;
  setLayout(mainLayout);
}

QtWindow::~QtWindow() {
}

void QtWindow::mouseLook(int x, int y) {
  LogDebug << x << y;
}

void QtWindow::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Escape:
            close();
        case Qt::Key_Shift:
            QtInput::Instance().inputSpeed = .5;
        case Qt::Key_W:
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_D:
            if (!QtInput::Instance().pressedKeys.contains(e->key()))
                QtInput::Instance().pressedKeys.push_back(e->key());
            QtInput::Instance().inputTimer->start(0);
            break;
        default:
            break;
    }
}

void QtWindow::keyReleaseEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Shift:
            QtInput::Instance().inputSpeed = .1;
        case Qt::Key_W:
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_D:
            QtInput::Instance().pressedKeys.removeAll(e->key());
            if (QtInput::Instance().pressedKeys.size() == 0)
                QtInput::Instance().inputTimer->stop();
            break;
        default:
            break;
    }
}
