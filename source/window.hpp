#ifndef BUW_WINDOW_HPP
#define BUW_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <utility>
#include <array>
#include <string>

class Window
{
public:
  Window(std::pair<int, int> const& windowsize = std::make_pair(640, 480));
  ~Window();

  enum MouseButton
  {
    MOUSE_BUTTON_NONE   = 0,
    MOUSE_BUTTON_LEFT   = (1 << 0),
    MOUSE_BUTTON_RIGHT  = (1 << 1),
    MOUSE_BUTTON_MIDDLE = (1 << 2)
  };

  enum KeyAction
  {
    KEY_PRESS   = GLFW_PRESS,
    KEY_RELEASE = GLFW_RELEASE,
    KEY_REPEAT  = GLFW_REPEAT
  };

  // Draw a line starting at (startX,startY) to (endX, endY) with color (r,g,b)
  // where (startX,startY), (endX, endY) \in [0,1)^2 and (r,g,b) \in [0,1)^3
  void draw_line(float startX, float startY,
                float endX, float endY,
                float r, float g, float b
                ) const;


  // Draw a point at (x,y) with color (r,g,b)
  // where (x,y)\in [0,1)^2 and (r,g,b) \in [0,1)^3
  void draw_point(float x, float y, float r, float g, float b) const;

  // Return the mouse position in screen coordinates
  std::pair<int, int> mouse_position_in_screen_coordinates() const;

  // Return the mouse position in [0,1)^2
  std::pair<float, float> mouse_position() const;

  // is closed flag set
  bool should_close() const;


  // close window
  void close();

  // update window
  void update();

  // test if given key is pressed
  // See here for key codes:
  // http://www.glfw.org/docs/latest/group__keys.html
  inline bool is_key_pressed(int key) const { return m_keypressed[key]; }

  // current window size
  std::pair<int, int> window_size() const;

  // time elapsed since GLFW was initialized
  float get_time() const;

private:
  GLFWwindow* m_window;
  std::pair<int, int> m_size;
  std::string const m_title;
  std::pair<int, int> m_mouse_position;

  int m_mouse_button_flags;
  std::array<bool, 512> m_keypressed;

  static void cursorPositionCallback(GLFWwindow* win, double x, double y);
  static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
  static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
};

#endif // define BUW_WINDOW_HPP
