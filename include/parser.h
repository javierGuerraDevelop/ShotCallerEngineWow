#ifndef SHOTCALLERCPP_PARSER_H
#define SHOTCALLERCPP_PARSER_H

#include <chrono>
#include <string>

struct CombatEvent {
    std::chrono::system_clock::time_point time_stamp;
    std::string event_type;
    std::string name;
    std::string source_id;
    std::string target_id;
    std::string source_raid_flag;
    std::string spell_name;
    int spell_id;
};

CombatEvent parse_line(const std::string& string);
std::chrono::time_point<std::chrono::system_clock> parse_timestamp(const std::string&);

#endif  // SHOTCALLERCPP_PARSER_H
