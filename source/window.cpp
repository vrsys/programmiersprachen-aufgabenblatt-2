#define NANOVG_GLEW

#include <cstdio>
#ifdef NANOVG_GLEW
#	include <GL/glew.h>
#endif
#ifdef __APPLE__
#	define GLFW_INCLUDE_GLCOREARB
#endif
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"


#include "window.hpp"
#include <utility>
#include <cstring>
#include <iostream>
#include <cassert>
#include <exception>

namespace {
void errorcb(int error, const char* desc)
{
  std::cerr << "GLFW error " << error << ": " << desc << std::endl;
}
}

Window::Window(std::pair<int, int> const& windowsize)
  : m_window{nullptr}
  , m_nvgContext{nullptr}
  , m_windowSize{windowsize}
  , m_framebufferSize{windowsize}
  , m_title("Fensterchen")
  , m_font_normal{0}
{
  if (!glfwInit()) {
    throw "Could not init glfw";
  }
  glfwSetErrorCallback(errorcb);
  //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

  glfwWindowHint(GLFW_RESIZABLE, 0);

  m_window = glfwCreateWindow(windowsize.first, windowsize.second, m_title.c_str(), nullptr, nullptr);
  if (!m_window) {
    glfwTerminate();
    throw "Could not create window";
  }

  glfwMakeContextCurrent(m_window);

  //  the pollable state of a mouse button will remain GLFW_PRESS until the
  //  state of that button is polled with glfwGetMouseButton. Once it has been
  //  polled, if a mouse button release event had been processed in the
  //  meantime, the state will reset to GLFW_RELEASE, otherwise it will remain
  //  GLFW_PRESS.
  glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, 1);

  glfwSetWindowUserPointer(m_window, this);
  assert(m_window != nullptr);


#ifdef NANOVG_GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
      throw "Could not init glew";
  }
  glGetError();
#endif
  m_nvgContext = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
  if (m_nvgContext == nullptr) {
      throw "Could not init nanovg";
  }

  m_font_normal = nvgCreateFont(m_nvgContext, "sans", "Roboto-Regular.ttf");
  if (m_font_normal == -1) {
    throw "Could not add font italic.";
  }

  // Begin Frame
  glfwGetFramebufferSize(m_window, &m_framebufferSize.first, &m_framebufferSize.second);

  // Calculate pixel ration for hi-dpi devices.
  float pxRatio = float(m_framebufferSize.first) / float(m_windowSize.first);
  glViewport(0, 0, m_framebufferSize.first, m_framebufferSize.second);
  //glClearColor(1.0f,1.0f,1.0f,1.0f);
  glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  nvgBeginFrame(m_nvgContext, m_windowSize.first, m_windowSize.second, pxRatio);
}

Window::~Window()
{
  glfwTerminate();
}

int Window::get_key(int key) const
{
  return glfwGetKey(m_window, key);
}

int Window::get_mouse_button(int button) const
{
  return glfwGetMouseButton(m_window, button);
}

bool Window::should_close() const
{
  return glfwWindowShouldClose(m_window);
}

std::pair<double, double> Window::mouse_position() const
{
  double xpos=0.0;
  double ypos=0.0f;
  glfwGetCursorPos(m_window, &xpos, &ypos);
  return {xpos, ypos};
}

void Window::close()
{
  glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::update()
{
  // End Frame
  nvgEndFrame(m_nvgContext);
  glfwSwapBuffers(m_window);
  glfwPollEvents();

  // Begin Frame
  glViewport(0, 0, m_framebufferSize.first, m_framebufferSize.second);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // Calculate pixel ration for hi-dpi devices.
  float pxRatio = float(m_framebufferSize.first) / float(m_windowSize.first);
  nvgBeginFrame(m_nvgContext, m_windowSize.first, m_windowSize.second, pxRatio);
}

std::pair<int, int> Window::window_size() const
{
  std::pair<int, int> size(0,0);
  glfwGetFramebufferSize(m_window, &size.first, &size.second);
  return size;
}

void Window::draw_line(float startX, float startY,
                float endX, float endY,
                float r, float g, float b
                ) const
{
  nvgSave(m_nvgContext);

  nvgBeginPath(m_nvgContext);
  nvgLineCap(m_nvgContext, NVG_ROUND);
  nvgLineJoin(m_nvgContext, NVG_BEVEL);
  nvgStrokeColor(m_nvgContext, nvgRGBA(r*255.0f,g*255.0f,b*255.0f,160));
  nvgStrokeWidth(m_nvgContext, 3.0f);
  nvgMoveTo(m_nvgContext, startX, startY);
  nvgLineTo(m_nvgContext, endX, endY);
  nvgStroke(m_nvgContext);

  nvgRestore(m_nvgContext);
}

void Window::draw_point(float x, float y, float r, float g, float b) const
{
  nvgSave(m_nvgContext);
  nvgBeginPath(m_nvgContext);
  nvgCircle(m_nvgContext, x, y, 2);

  auto col = nvgRGBA(r*255.0f,g*255.0f,b*255.0f,255);
  nvgFillColor(m_nvgContext, col);
  nvgFill(m_nvgContext);
  nvgStrokeColor(m_nvgContext, col);
  nvgStroke(m_nvgContext);
  nvgRestore(m_nvgContext);
}

void Window::draw_text(float x, float y, float font_size, std::string const& text) const
{
  nvgSave(m_nvgContext);
  nvgFontSize(m_nvgContext, font_size);
  nvgFontFace(m_nvgContext, "sans");
  nvgTextAlign(m_nvgContext, NVG_ALIGN_LEFT|NVG_ALIGN_TOP);

  nvgFillColor(m_nvgContext, nvgRGBA(255, 255, 255, 255));
  nvgText(m_nvgContext, x, y, text.c_str(), nullptr);
  nvgRestore(m_nvgContext);
}

float Window::get_time() const
{
  return float(glfwGetTime());
}
