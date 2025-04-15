#include <vec2.hpp>
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <utility>
#include <cmath>


int main(int argc, char* argv[])
{
  buw::Window win{std::make_pair(800,800)};

  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }

    bool left_pressed = win.get_mouse_button(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    auto t = win.get_time();

    double x1 = 400.0 + 380.0 * std::sin(t);
    double y1 = 400.0 + 380.0 * std::cos(t);

    double x2 = 400.0 + 380.0 * std::sin(2.0*t);
    double y2 = 400.0 + 380.0 * std::cos(2.0*t);

    double x3 = 400.0 + 380.0 * std::sin(t-10.0);
    double y3 = 400.0 + 380.0 * std::cos(t-10.0);

    win.draw_point(x1, y1, 1.0, 0.0, 0.0);
    win.draw_point(x2, y2, 0.0, 1.0, 0.0);
    win.draw_point(x3, y3, 0.0, 0.0, 1.0);

    auto mouse_position = win.mouse_position();
    if (left_pressed) {
      win.draw_line(30.0, 30.0, // FROM pixel idx with coords (x=30, y=30)
                    mouse_position.first, mouse_position.second, // TO mouse position in pixel coords
                    1.0,0.0,0.0, // color with r,g,b in [0.0, 1.0]
                    1.0);        // line thickness = 1.0 * default thickness
    }

    win.draw_line(0, mouse_position.second, 10, mouse_position.second, 0.0, 0.0, 0.0);
    win.draw_line(win.window_size().second - 10, mouse_position.second, win.window_size().second, mouse_position.second, 0.0, 0.0, 0.0);

    win.draw_line(mouse_position.first, 0, mouse_position.first, 10, 0.0, 0.0, 0.0);
    win.draw_line(mouse_position.first, win.window_size().second - 10, mouse_position.first, win.window_size().second, 0.0, 0.0, 0.0);

    std::string display_text = "mouse position: (" + std::to_string(mouse_position.first) + ", " + std::to_string(mouse_position.second) + ")";
    
    double text_offset_x = 10.0;
    double text_offset_y =  5.0;
    unsigned int font_size = 35;
    
    win.draw_text(text_offset_x, text_offset_y, font_size, display_text);

    win.update();
  }

  return 0;
}
