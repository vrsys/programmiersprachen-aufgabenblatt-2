#include "Roboto-Regular_ttf_binary.hpp"

#define NANOVG_GLEW

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

#include <cstdio>

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

namespace buw {
    Window::Window(std::pair<int, int> const& windowsize)
        : window_{ nullptr }
        , nanovg_context_{ nullptr }
        , window_size_{ windowsize }
        , framebuffer_size_{ windowsize }
        , title_("Programmiersprachen Aufgabenblatt 2")
        , normal_font_{ 0 }
    {
        if (!glfwInit()) {
            throw "Could not initialize GLFW";
        }
        glfwSetErrorCallback(errorcb);
        //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#endif //DEBUG
        glfwWindowHint(GLFW_RESIZABLE, 0);

        window_ = glfwCreateWindow(windowsize.first, windowsize.second, title_.c_str(), nullptr, nullptr);
        if (!window_) {
            glfwTerminate();
            throw "Could not create window";
        }

        glfwMakeContextCurrent(window_);

        //  the pollable state of a mouse button will remain GLFW_PRESS until the
        //  state of that button is polled with glfwGetMouseButton. Once it has been
        //  polled, if a mouse button release event had been processed in the
        //  meantime, the state will reset to GLFW_RELEASE, otherwise it will remain
        //  GLFW_PRESS.
        glfwSetInputMode(window_, GLFW_STICKY_MOUSE_BUTTONS, 1);

        glfwSetWindowUserPointer(window_, this);
        assert(window_ != nullptr);


#ifdef NANOVG_GLEW
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            throw "Could not init glew";
        }
        glGetError();
#endif
        nanovg_context_ = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
        if (nanovg_context_ == nullptr) {
            std::cout << "Could not init nanovg" << std::endl;
            throw "Could not init nanovg";
        }

        normal_font_ = nvgCreateFontMem(nanovg_context_, "sans", (unsigned char*)(Roboto_Regular_ttf_binarized.data()), static_cast<int>(Roboto_Regular_ttf_binarized.size()), 0);
        if (normal_font_ == -1) {
            std::cout << "Could not load font file" << std::endl;
            throw "Could not load font file.";
        }

        // Begin Frame
        glfwGetFramebufferSize(window_, &framebuffer_size_.first, &framebuffer_size_.second);

        // Calculate pixel ratio for hi-dpi devices.
        double pixel_aspect_ratio = double(framebuffer_size_.first) / double(window_size_.first);
        glViewport(0, 0, framebuffer_size_.first, framebuffer_size_.second);

        glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        nvgBeginFrame(nanovg_context_, window_size_.first, window_size_.second, static_cast<float>(pixel_aspect_ratio));
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    int Window::get_key(int key) const
    {
        return glfwGetKey(window_, key);
    }

    int Window::get_mouse_button(int button) const
    {
        return glfwGetMouseButton(window_, button);
    }

    bool Window::should_close() const
    {
        return glfwWindowShouldClose(window_);
    }

    std::pair<double, double> Window::mouse_position() const
    {
        double xpos = 0.0;
        double ypos = 0.0f;
        glfwGetCursorPos(window_, &xpos, &ypos);
        return { xpos, ypos };
    }

    void Window::close()
    {
        glfwSetWindowShouldClose(window_, GL_TRUE);
    }

    void Window::update()
    {
        // End Frame
        nvgEndFrame(nanovg_context_);
        glfwSwapBuffers(window_);
        glfwPollEvents();

        // Begin Frame
        glViewport(0, 0, framebuffer_size_.first, framebuffer_size_.second);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Calculate pixel ration for hi-dpi devices.
        double pxRatio = static_cast<double>(framebuffer_size_.first) / static_cast<float>(window_size_.first);
        nvgBeginFrame(nanovg_context_, window_size_.first, window_size_.second, static_cast<float>(pxRatio) );
    }

    std::pair<int, int> Window::window_size() const
    {
        std::pair<int, int> size(0, 0);
        glfwGetFramebufferSize(window_, &size.first, &size.second);
        return size;
    }

    void Window::draw_line(double starting_pos_x, double starting_pos_y,
                           double end_pos_x, double end_pos_y,
                           double r, double g, double b,
                           double thickness
    ) const
    {
        nvgSave(nanovg_context_);

        nvgBeginPath(nanovg_context_);
        nvgLineCap(nanovg_context_, NVG_ROUND);
        nvgLineJoin(nanovg_context_, NVG_BEVEL);
        nvgStrokeColor(nanovg_context_, nvgRGBA(static_cast<unsigned char>(r * 255.0), static_cast<unsigned char>(g * 255.0), static_cast<unsigned char>(b * 255.0), 160));
        nvgStrokeWidth(nanovg_context_, thickness * 3.0f);
        nvgMoveTo(nanovg_context_, static_cast<float>(starting_pos_x), static_cast<float>(starting_pos_y));
        nvgLineTo(nanovg_context_, static_cast<float>(end_pos_x), static_cast<float>(end_pos_y));
        nvgStroke(nanovg_context_);

        nvgRestore(nanovg_context_);
    }

    void Window::draw_point(double pos_x, double pos_y, double normalized_red_component, double normalized_green_component, double normalized_blue_component) const
    {
        nvgSave(nanovg_context_);
        nvgBeginPath(nanovg_context_);
        nvgCircle(nanovg_context_, pos_x, pos_y, 2);

        auto col = nvgRGBA(static_cast<unsigned char>(normalized_red_component * 255.0f), static_cast<unsigned char>(normalized_green_component * 255.0f), static_cast<unsigned char>(normalized_blue_component * 255.0f), 255);
        nvgFillColor(nanovg_context_, col);
        nvgFill(nanovg_context_);
        nvgStrokeColor(nanovg_context_, col);
        nvgStroke(nanovg_context_);
        nvgRestore(nanovg_context_);
    }

    void Window::draw_text(double pos_x, double pos_y, double font_size, std::string const& text) const
    {
        nvgSave(nanovg_context_);
        nvgFontSize(nanovg_context_, static_cast<float>(font_size));
        nvgFontFace(nanovg_context_, "sans");
        nvgTextAlign(nanovg_context_, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);

        nvgFillColor(nanovg_context_, nvgRGBA(255, 255, 255, 255));
        nvgText(nanovg_context_, static_cast<float>(pos_x), static_cast<float>(pos_y), text.c_str(), nullptr);
        nvgRestore(nanovg_context_);
    }

    double Window::get_time() const
    {
        return glfwGetTime();
    }

} //namespace buw