/*
 * Copyright © 2010 Lubosz Sarnecki
 * Input.h
 *
 *  Created on: Sep 28, 2010
 */

#pragma once

#include <QList>
#include <QTimer>
#include "Shader/ShaderProgram.h"
#include <xcb/xcb_keysyms.h>
#include "Application/Input.h"

class XCBWindow;

class XCBInput : public Input {
 Q_OBJECT
public:

  explicit XCBInput(xcb_connection_t *connection, XCBWindow * mediaLayer);
  virtual ~XCBInput();
public slots:
  void eventLoop();

private:

#ifdef XCBEVENTS

  xcb_event_handlers_t *evenths;

#define HANDLER_DECLARE(event, name)\
			  static int Handle##name(void*, xcb_connection_t*, xcb_##event##_event_t*)

  HANDLER_DECLARE(motion_notify, MotionNotify);
  HANDLER_DECLARE(key_press, KeyPress);
  HANDLER_DECLARE(key_release, KeyRelease);
#undef HANDLER_DECLARE

#endif

  xcb_connection_t *connection;
  QTimer *eventTimer;
  xcb_key_symbols_t *syms;
  xcb_keysym_t pressedKey;

  QList<xcb_keysym_t> pressedKeys;
  XCBWindow * mediaLayer;

  int16_t lastEventX, lastEventY;

  void checkKey(xcb_keysym_t pressedKey);

};
