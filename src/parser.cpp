#include "parser.h"

#include <cctype>
#include <string>

namespace ch = std::chrono;
using std::get_time;
using std::getline;
using std::mktime;
using std::stoi;
using std::string;
using std::stringstream;
using std::tm;
using std::vector;

bool HasLetters(const std::string& str)
{
    for (unsigned char c : str)
        if (std::isalpha(c))
            return true;

    return false;
}

ch::time_point<ch::system_clock> ParseTimestamp(const string& timestamp)
{
    if (HasLetters(timestamp))
        return {};

    size_t tz_pos = timestamp.find_last_of("+-");
    if (tz_pos == string::npos)
        return {};

    int tz_offset_hours = stoi(timestamp.substr(tz_pos));

    string main_part = timestamp.substr(0, tz_pos);

    size_t ms_pos = main_part.find('.');
    if (ms_pos == string::npos)
        return {};

    string datetime_part = timestamp.substr(0, ms_pos);
    int ms = stoi(main_part.substr(ms_pos + 1));

    tm time_struct{};
    stringstream stream{ datetime_part };
    stream >> get_time(&time_struct, "%m/%d/%Y/%H/%M/%S");

    time_t time = mktime(&time_struct);
    auto time_point = ch::system_clock::from_time_t(time);
    time_point += ch::milliseconds(ms);
    time_point -= ch::hours(tz_offset_hours);

    return time_point;
}

CombatEvent ParseLine(const string& line)
{
    if (line.empty())
        return CombatEvent{};

    string field{};
    vector<string> data{};
    stringstream stream{ line };
    CombatEvent event{};

    while (getline(stream, field, ','))
        data.push_back(field);

    if (data.size() < 10)
        return {};

    size_t space_pos = data[0].find("  ");
    if (space_pos != string::npos) {
        string timestamp_str = data[0].substr(0, space_pos);
        event.time_stamp = ParseTimestamp(timestamp_str);
        event.event_type = data[0].substr(space_pos + 2);
    }

    stringstream name_stream{ data[2] };
    string player_name{};
    getline(name_stream, player_name, '-');
    player_name.erase(std::remove(player_name.begin(), player_name.end(), '\"'), player_name.end());

    event.name = player_name;
    event.source_id = data[1];
    event.source_raid_flag = data[3];
    event.target_id = data[5];

    std::string spell_name = data[10];
    spell_name.erase(std::remove(spell_name.begin(), spell_name.end(), '\"'), spell_name.end());
    event.spell_name = spell_name;
    event.spell_id = std::stoi(data[9]);

    return event;
}
