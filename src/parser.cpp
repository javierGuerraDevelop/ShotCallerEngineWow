#include "parser.h"

#include "constants.h"

namespace ch = std::chrono;

ch::time_point<ch::system_clock> ParseTimestamp(const std::string& timestamp) {
    size_t tz_pos = timestamp.find_last_of("+-");
    if (tz_pos == std::string::npos) {
        return {};
    }

    int tz_offset_hours = std::stoi(timestamp.substr(tz_pos));

    std::string main_part = timestamp.substr(0, tz_pos);

    size_t ms_pos = main_part.find('.');
    if (ms_pos == std::string::npos) {
        return {};
    }

    std::string datetime_part = timestamp.substr(0, ms_pos);
    int ms = std::stoi(main_part.substr(ms_pos + 1));

    std::tm time_struct{};
    std::stringstream stream{datetime_part};
    stream >> std::get_time(&time_struct, "%m/%d/%Y/%H/%M/%S");

    time_t time = std::mktime(&time_struct);
    auto time_point = ch::system_clock::from_time_t(time);
    time_point += ch::milliseconds(ms);
    time_point -= ch::hours(tz_offset_hours);

    return time_point;
}

CombatEvent ParseLine(const std::string& line) {
    if (line.empty()) {
        return {};
    }

    std::string field{};
    std::vector<std::string> data{};
    std::stringstream stream{line};
    CombatEvent event{};

    while (std::getline(stream, field, ',')) {
        data.push_back(field);
    }

    size_t space_pos = data[0].find("  ");
    if (space_pos != std::string::npos) {
        std::string timestamp_str = data[0].substr(0, space_pos);
        event.time_stamp = ParseTimestamp(timestamp_str);
        event.event_type = data[0].substr(space_pos + 2);
    }

    if (!Constants::IsValidEvent(event.event_type)) {
        return {};
    }

    std::stringstream name_stream{data[2]};
    std::string player_name{};
    std::getline(name_stream, player_name, '-');
    player_name.erase(std::remove(player_name.begin(), player_name.end(), '\"'),
                      player_name.end());

    std::string spell_name = data[10];
    spell_name.erase(std::remove(spell_name.begin(), spell_name.end(), '\"'),
                     spell_name.end());

    event.player_name = player_name;
    event.source_id = data[1];
    event.source_raid_flag = data[3];
    event.target_id = data[5];
    event.spell_name = spell_name;
    event.spell_id = std::stoi(data[9]);

    return event;
}
