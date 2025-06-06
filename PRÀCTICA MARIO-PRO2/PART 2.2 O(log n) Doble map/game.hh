#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "strawberry.hh"
#include "finder.hh"

class Game {
    std::vector<Strawberry> strawberrys_;
    int strawberry_count_ = 0;

    Mario                 mario_;
    std::vector<Platform> platforms_;

    bool finished_;

    Finder<Platform> platform_finder_;
    Finder<Strawberry> strawberry_finder_;
    set<Platform*> visible_platforms_;
    set<Strawberry*> visible_strawberrys_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif