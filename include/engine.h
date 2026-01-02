#include <array>
#include <functional>
#include <tuple>
#include <vector>

#include "parser.h"

#ifndef SHOTCALLERENGINEWOW_ENGINE_H
#define SHOTCALLERENGINEWOW_ENGINE_H

template <typename T>
struct Event {
    std::function<void()> func_ptr;
    std::vector<std::tuple<T>> arguments;
    std::chrono::steady_clock::time_point execute_time;
    bool is_executed;
};

struct Shotcall {
    std::string message;
    std::chrono::steady_clock::time_point execute_time;
    bool is_executed;

    // operator overload for priority queue ordering
    bool operator>(const Shotcall& other) const {
        return execute_time > other.execute_time;
    }
};

class Engine {
   private:
    std::vector<Shotcall> pipeline_;

   public:
    void HandleEnemyEvent();
    void HandlePlayerEvent();
    void HandlePlayerDeath();
    void HandleEnemyDeath();
    void ExecuteShotcall();  // read 2s before to give players time to react
    void IdentifyEntity();

    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine) = delete;
};

struct Ability {
    int spellid;
    std::string spellname;
    std::chrono::seconds cooldown;
    bool is_ready;
    std::chrono::time_point<std::chrono::system_clock> on_cooldown_until{};

    Ability() {}
};

struct Player {
    std::string uuid;
    std::string name;
    Ability interrupt;
    std::array<Ability, 5> cc_arr;
    bool is_alive{true};
    bool is_ccd{false};

    Player() {}

    void SetAlive() { is_alive = true; }
    void SetDead() { is_alive = false; }
    void SetCcDuration(Ability ability) {
        auto x = ability.cooldown;
        ;
    }
};

struct Enemy {
    std::string uuid;
    std::string name;
    std::array<Ability, 5> ability_arr;
};

#endif  // SHOTCALLERENGINEWOW_ENGINE_H
