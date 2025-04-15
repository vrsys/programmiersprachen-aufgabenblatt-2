#ifndef BUW_WINDOW_HPP
#define BUW_WINDOW_HPP


#include <array>
#
#include <string>
#include <utility>

struct NVGcontext;
struct GLFWwindow;

namespace buw {

    class Window
    {
    public:
        Window(std::pair<int, int> const& windowsize = std::make_pair(640, 480));
        ~Window();

        // Draw a line starting at (starting_pos_x, starting_pos_y) to (end_pos_x, end_pos_y) with color (r,g,b)
        // where (starting_pos_x, starting_pos_y), (end_pos_x, end_pos_y) \in [0,1)^2 and (r,g,b) \in [0,1)^3
        void draw_line(double starting_pos_x, double starting_pos_y,
                       double end_pos_x, double end_pos_y,
                       double r, double g, double b,
                       double thickness = 1.0
        ) const;


        // Draw a point at (x,y) with color (r,g,b)
        // where (x,y)\in [0,1)^2 and (r,g,b) \in [0,1)^3
        void draw_point(double x, double y, double r, double g, double b) const;

        void draw_text(double x, double y, double font_size, std::string const& text) const;

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
        double get_time() const;

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

} //namespace buw

#endif // define BUW_WINDOW_HPP
