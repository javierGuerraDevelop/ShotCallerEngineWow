#include <array>
#include <functional>
#include <tuple>
#include <vector>

#include "parser.h"

#ifndef SHOTCALLERENGINEWOW_ENGINE_H
#define SHOTCALLERENGINEWOW_ENGINE_H

template <typename T>
struct Event {
    std::function<void()> func_ptr{};
    std::vector<std::tuple<T>> arguments{};
    std::chrono::steady_clock::time_point execute_time{};
    bool is_executed;
};

struct Shotcall {
    std::string message{};
    std::chrono::steady_clock::time_point execute_time{};
    bool is_executed{};

    bool operator>(const Shotcall& other) const {
        return execute_time > other.execute_time;
    }
};

struct Ability {
    int spellid{};
    std::string spellname{};
    std::chrono::seconds cooldown{};
    bool is_ready{};
    std::chrono::time_point<std::chrono::system_clock> on_cooldown_until{};

    Ability() {}
};

struct Player {
    std::string uuid{};
    std::string name{};
    Ability interrupt{};
    std::array<Ability, 5> cc_arr{};
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
    std::string uuid{};
    std::string name{};
    std::array<Ability, 5> ability_arr{};
};

class Engine {
   private:
    std::vector<Shotcall> pipeline_{};
    void RemoveCc(Player&);
    void ExecuteShotcall(const Shotcall&);
    void IdentifyEvent(const CombatEvent&);
    void HandleEnemyEvent(const CombatEvent&);
    void HandlePlayerEvent(const CombatEvent&);
    void HandlePlayerDeath(Player&);
    void HandleEnemyDeath(Enemy&);
    void IdentifyEntity(const CombatEvent&);

   public:
    void RunEngine() {}

    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine) = delete;
};

#endif  // SHOTCALLERENGINEWOW_ENGINE_H
