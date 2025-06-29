#pragma once
#ifndef NIBBLER_GRAPHICS_API
#define NIBBLER_GRAPHICS_API

#include <memory>
#include <functional>

namespace nibbler {

enum KEY {
    ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT,
    NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9, NUMBER_0,
    LETTER_P,
};

class IWindow {
public:
    typedef std::function<void(KEY)> KeyDownCallback, KeyUpCallback, KeyPressCallback;

    IWindow() = delete;
    inline virtual ~IWindow() {};

    virtual void add_event_listener_key_down(KeyDownCallback cb) = 0;
    virtual void add_event_listener_key_up(KeyUpCallback cb) = 0;
    virtual void add_event_listener_key_press(KeyPressCallback cb) = 0;
    virtual void draw_pixel(size_t x, size_t y) = 0;
    virtual void clear_screen() = 0;

protected:
    inline IWindow(size_t width, size_t height, std::string title) {};
};

class INibblerGraphicsApi {

public:
    inline virtual ~INibblerGraphicsApi() {};
    virtual std::shared_ptr<IWindow> create_window(size_t width, size_t height, std::string title) = 0;
};

typedef INibblerGraphicsApi* (*INibblerGraphicsApiConstructor)();
typedef void (*INibblerGraphicsApiDestructor)(INibblerGraphicsApi*);  
typedef std::unique_ptr<INibblerGraphicsApi, INibblerGraphicsApiDestructor> GraphicsApiUniquePtr;

}

extern "C" {
  nibbler::INibblerGraphicsApi* create_graphics_library();
  void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib);
}

#endif