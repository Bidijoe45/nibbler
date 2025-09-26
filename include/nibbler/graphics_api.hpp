#pragma once
#ifndef NIBBLER_GRAPHICS_API
#define NIBBLER_GRAPHICS_API

#include <memory>
#include <functional>

namespace nibbler {

enum Key {
    ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT,
    NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9, NUMBER_0,
    ESC, LETTER_P, EMPTY
};

struct Position {
    int x;
    int y;
};

class IWindow {
public:
    typedef std::function<void(Key)> Callback, KeyDownCallback, KeyUpCallback, KeyPressCallback;

    IWindow() = delete;
    inline virtual ~IWindow() {}

    virtual void add_event_listener_key_down(KeyDownCallback cb) = 0;
    virtual void add_event_listener_key_up(KeyUpCallback cb) = 0;
    virtual void add_event_listener_key_press(KeyPressCallback cb) = 0;
    virtual void clear_screen() = 0;
    virtual void read_input() = 0;
    virtual void draw_snake(const std::vector<Position> &snake) = 0;
    virtual void draw_fruit(const Position& fruit_pos) = 0;
    virtual void set_score(int score) = 0;
    virtual void render() = 0;
    virtual void push_message(const std::string &msg) = 0;

protected:
    inline IWindow(size_t width_squares, size_t height_squares, std::string title) {}
};

class INibblerGraphicsApi {

public:
    inline virtual ~INibblerGraphicsApi() {};
    virtual std::unique_ptr<IWindow> create_window(size_t width_squares, size_t height_squares, std::string title) = 0;
};

typedef INibblerGraphicsApi* (*INibblerGraphicsApiConstructor)();
typedef void (*INibblerGraphicsApiDestructor)(INibblerGraphicsApi*);  
typedef std::unique_ptr<INibblerGraphicsApi, INibblerGraphicsApiDestructor> GraphicsApiUniquePtr;
typedef std::shared_ptr<INibblerGraphicsApi> GraphicsApiSharedPtr;

}

extern "C" {
    nibbler::INibblerGraphicsApi* create_graphics_library();
    void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib);
}

#endif