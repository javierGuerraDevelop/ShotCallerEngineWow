#ifndef SHOTCALLERCPP_PARSER_H
#define SHOTCALLERCPP_PARSER_H

#include <chrono>
#include <string>

struct CombatEvent {
    std::chrono::system_clock::time_point time_stamp;
    std::string event_type;
    std::string player_name;
    std::string source_id;
    std::string target_id;
    std::string source_raid_flag;
    std::string spell_name;
    int spell_id;

    bool operator==(const CombatEvent& other) const
    {
        return (time_stamp == other.time_stamp) && (event_type == other.event_type) &&
               (player_name == other.player_name) && (source_id == other.source_id) &&
               (target_id == other.target_id) && (source_raid_flag == other.source_raid_flag) &&
               (spell_name == other.spell_name) && (spell_id == other.spell_id);
    }
};

CombatEvent ParseLine(const std::string& string);
std::chrono::time_point<std::chrono::system_clock> ParseTimestamp(const std::string&);

#endif  // SHOTCALLERCPP_PARSER_H
