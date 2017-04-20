#ifndef BUW_WINDOW_HPP
#define BUW_WINDOW_HPP

#include <utility>
#include <array>
#include <string>

struct NVGcontext;
struct GLFWwindow;

class Window
{
public:
  Window(std::pair<int, int> const& windowsize = std::make_pair(640, 480));
  ~Window();

  // Draw a line starting at (startX,startY) to (endX, endY) with color (r,g,b)
  // where (startX,startY), (endX, endY) \in [0,1)^2 and (r,g,b) \in [0,1)^3
  void draw_line(float startX, float startY,
                float endX, float endY,
                float r, float g, float b
                ) const;


  // Draw a point at (x,y) with color (r,g,b)
  // where (x,y)\in [0,1)^2 and (r,g,b) \in [0,1)^3
  void draw_point(float x, float y, float r, float g, float b) const;

  void draw_text(float x, float y, float font_size, std::string const& text) const;

  // Return the mouse position in screen coordinates
  std::pair<double, double> mouse_position() const;

  // is closed flag set
  bool should_close() const;

  // close window
  void close();

  // update window
  void update();

  // test if given key is pressed
  // See here for key codes:
  // http://www.glfw.org/docs/latest/group__keys.html
  int get_key(int key) const;
  int get_mouse_button(int button) const;

  // current window size
  std::pair<int, int> window_size() const;

  // time elapsed since GLFW was initialized
  float get_time() const;

private:
  GLFWwindow* m_window;
  NVGcontext* m_nvgContext;
  std::pair<int, int> m_windowSize;
  std::pair<int, int> m_framebufferSize;
  std::string const m_title;

  int m_font_normal;
  int m_font_bold;
  int m_font_icons;
  int m_font_emoji;
};

#endif // define BUW_WINDOW_HPP
