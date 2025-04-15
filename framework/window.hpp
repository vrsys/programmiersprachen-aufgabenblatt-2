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


        // Draw a point at (pos_x,pos_y) with color (r, g, b)
        // where (pos_x, pos_y) is between 0 and width and height and (r,g,b) \in [0,1)^3
        void draw_point(double pos_x, double pos_y, double r, double g, double b) const;

        void draw_text(double pos_x, double pos_y, double font_size, std::string const& text) const;

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

        // get current window size
        std::pair<int, int> window_size() const;

        // time elapsed since GLFW was initialized
        double get_time() const;

    private:
        GLFWwindow* window_;
        NVGcontext* nanovg_context_;
        std::pair<int, int> window_size_;
        std::pair<int, int> framebuffer_size_;
        std::string const title_;

        int normal_font_;
    };

} //namespace buw

#endif // define BUW_WINDOW_HPP
