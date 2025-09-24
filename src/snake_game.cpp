#include "snake_game.hpp"

#include <thread>
#include <iostream>

namespace nibbler {
SnakeGame::SnakeGame(
    Configuration config,
    const std::map<Key, GraphicsApiSharedPtr> &graphics_apis
) : config_(config),
    graphics_apis_(graphics_apis),
    fruit_factory_(config_.gameboard_width_squares, config_.gameboard_height_squares)
{
    if (!graphics_apis.empty())
    {
        this->current_gui_ = this->graphics_apis_.begin()->first;
        this->switch_gui(); // create the initial window
    }
}

SnakeGame::~SnakeGame() {}

void SnakeGame::on_key_down(Key key) {

    switch (key) {
        case Key::ARROW_LEFT:
            this->snake_.change_direction(Direction::LEFT);
            break;
        case Key::ARROW_RIGHT:
            this->snake_.change_direction(Direction::RIGHT);
            break;
        case Key::ARROW_DOWN:
            this->snake_.change_direction(Direction::DOWN);
            break;
        case Key::ARROW_UP:
            this->snake_.change_direction(Direction::UP);
            break;
        case Key::ESC:
            this->game_state_ = GameState::END;
            break;
        case Key::NUMBER_1:
        case Key::NUMBER_2:
        case Key::NUMBER_3:
        case Key::NUMBER_4:
        case Key::NUMBER_5:
        case Key::NUMBER_6:
        case Key::NUMBER_7:
        case Key::NUMBER_8:
        case Key::NUMBER_9:
        case Key::NUMBER_0:
            // we don't update the gui directly here because the window
            // instance would be destroyed, and this function is passed as
            // a callback to, and called from, the window object
            this->current_gui_ = key;
            break;
        default:
            break;
    }
}

void SnakeGame::initialize_game() {

    Position start_pos;
    start_pos.x = this->config_.gameboard_width_squares / 2;
    start_pos.y = this->config_.gameboard_height_squares / 2;

    this->snake_ = Snake(start_pos);
    this->score_ = 0;
    this->fruit_ = fruit_factory_.create_fruit_random_pos();
}

// This function is called 59.9 times per second. Game logic goes here
void SnakeGame::update(double delta_time) {

    this->snake_.move(delta_time);

    // If collision, just restart the game for now
    bool wall_collision = this->snake_.check_wall_collision(this->config_.gameboard_width_squares, this->config_.gameboard_height_squares);
    bool body_collision = this->snake_.check_body_collision();
    if (wall_collision || body_collision) {
        this->initialize_game();
    }

    bool fruit_collision = this->snake_.check_fruit_collision(this->fruit_.pos);
    if (fruit_collision) {
        this->fruit_ = this->fruit_factory_.create_fruit_random_pos();
        this->score_ += 1;
        this->snake_.add_segment();
    }

    this->window_->clear_screen();
    this->window_->set_score(this->score_);
    this->window_->draw_snake(this->snake_.body.segments);
    this->window_->draw_fruit(this->fruit_.pos);
    this->window_->render();
}

void SnakeGame::switch_gui()
{
    auto api = this->graphics_apis_.find(this->current_gui_);
    if (api == this->graphics_apis_.end())
        return;

    this->window_ = api->second->create_window(
        this->config_.gameboard_width_squares,
        this->config_.gameboard_height_squares,
        "Nibbler");

    this->window_->add_event_listener_key_down(std::bind(&SnakeGame::on_key_down, this, std::placeholders::_1));
}

int SnakeGame::run() {

    if (this->graphics_apis_.empty())
    {
        std::cerr << "Error: no graphics APIs" << std::endl;
        return 1;
    }

    const size_t target_frames_per_s = 60;
    const std::chrono::nanoseconds target_frame_duration(std::chrono::nanoseconds(std::chrono::seconds(1)) / target_frames_per_s);
    std::chrono::steady_clock::time_point previous_time = std::chrono::steady_clock::now();
    
    this->game_state_ = GameState::INIT;
    this->initialize_game();

    Key prev_gui = this->current_gui_;

    this->game_state_ = GameState::RUNNING;
    while (this->game_state_ == GameState::RUNNING) {

        std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
        std::chrono::duration<double> delta_time_s = frame_start - previous_time;
        previous_time = frame_start;
        
        this->window_->read_input();

        if (this->current_gui_ != prev_gui) {
            this->switch_gui();
            prev_gui = this->current_gui_;
        }

        this->update(delta_time_s.count());

        // double fps = 1.0 / delta_time.count();
        // std::cout << "FPS: " << fps << "\n";

        // TODO: maybe in the future add a sleep to reduce the %CPU usage

        while (std::chrono::steady_clock::now() - frame_start < target_frame_duration) {
            std::this_thread::yield();
        }
    }
    return 0;
}

}