#include "window.hpp"
#include <utility>
#include <cstring>
#include <iostream>
#include <cassert>

Window::Window(std::pair<int, int> const& windowsize)
  : m_window{nullptr}
  , m_size{windowsize}
  , m_title("Fensterchen")
  , m_mouse_position{}
  , m_mouse_button_flags{0}
  , m_keypressed{}
{
  std::fill(std::begin(m_keypressed), std::end(m_keypressed), 0);
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  m_window = glfwCreateWindow(windowsize.first, windowsize.second, m_title.c_str(), nullptr, nullptr);

  if (m_window) {
    glfwSetWindowUserPointer(m_window, this);
    assert(m_window != nullptr);

    glfwSetMouseButtonCallback(m_window, Window::mouseButtonCallback);
    glfwSetCursorPosCallback(m_window, Window::cursorPositionCallback);
    glfwSetKeyCallback(m_window, Window::keyCallback);
    glfwMakeContextCurrent(m_window);

    glewInit();

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(5.0f);
    glEnable(GL_POINT_SMOOTH);

    glLineWidth(2.0f);
    glEnable(GL_LINE_SMOOTH);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
  }
}

Window::~Window()
{
  if (m_window) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
  }
  glfwTerminate();
}

void Window::cursorPositionCallback(GLFWwindow* win, double x, double y)
{
  Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
  if (w) {
    w->m_mouse_position = std::make_pair(x, y);
  }
}

void Window::mouseButtonCallback(GLFWwindow* win, int button, int act, int mods)
{
  Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
  assert(w);

  if (GLFW_PRESS == act) {
      switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
          w->m_mouse_button_flags |= Window::MOUSE_BUTTON_LEFT;
          break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
          w->m_mouse_button_flags |= Window::MOUSE_BUTTON_MIDDLE;
          break;
        case GLFW_MOUSE_BUTTON_RIGHT:
          w->m_mouse_button_flags |= Window::MOUSE_BUTTON_RIGHT;
          break;
        default:
          break;
      }
  } else if (act == GLFW_RELEASE) {
    switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:
        w->m_mouse_button_flags &= ~Window::MOUSE_BUTTON_LEFT;
        break;
      case GLFW_MOUSE_BUTTON_MIDDLE:
        w->m_mouse_button_flags &= ~Window::MOUSE_BUTTON_MIDDLE;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:
        w->m_mouse_button_flags &= ~Window::MOUSE_BUTTON_RIGHT;
        break;
      default:
        break;
    }
  }
}

void Window::keyCallback(GLFWwindow* win, int key, int scancode, int act, int mods)
{
  Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
  if (w) {
    w->m_keypressed[key] = act == KEY_PRESS;
  }
}

bool Window::should_close() const
{
  return glfwWindowShouldClose(m_window);
}

std::pair<int, int> Window::mouse_position_in_screen_coordinates() const
{
  return m_mouse_position;
}

std::pair<float, float> Window::mouse_position() const
{
  return std::make_pair(float(m_mouse_position.first)/float(m_size.first)
         , 1.0f - float(m_mouse_position.second)/float(m_size.second));
}

void Window::close()
{
  glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::update()
{
  glfwSwapBuffers(m_window);
  glfwPollEvents();

  // prepare next frame
  glViewport(0, 0, m_size.first, m_size.second);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,0.01,100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -100.0);
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
  glColor3f(r, g, b);
  glBegin(GL_LINES);
  {
    glVertex2f(startX, startY);
    glVertex2f(endX, endY);
  }
  glEnd();

}

void Window::draw_point(float x, float y, float r, float g, float b) const
{
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
    glVertex2f(x, y);
  glEnd();
}

float Window::get_time() const
{
  return float(glfwGetTime());
}
