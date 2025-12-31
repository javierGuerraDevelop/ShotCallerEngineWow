#include "parser.h"

#include <gtest/gtest.h>

namespace ch = std::chrono;

static const CombatEvent test_event = { ParseTimestamp("6/14/2025 18:30:30.349-4"),
                                        "SPELL_PERIODIC_HEAL",
                                        "Bigchalupa",
                                        "Player-3676-0CD71E8D",
                                        "Player-76-0BED3564",
                                        "0x511",
                                        "Eternal Flame",
                                        156322 };

static const std::string test_string =
    R"(6/14/2025 18:30:30.349-4  SPELL_PERIODIC_HEAL,Player-3676-0CD71E8D,"Bigchalupa-Area52-US",0x511,0x0,Player-76-0BED3564,"Darthdemonic-Sargeras-US",0x512,0x0,156322,"Eternal Flame",0x6,Player-76-0BED3564,0000000000000000,7574108,10997049,13305,97197,39210,117,300,27243,0,2423075,2500000,0,2660.46,-5010.41,2335,3.2456,676,18846,18846,0,0,nil)";

TEST(ParserTest, ParseTimeStamp_ValidTimeStamp)
{
    ch::time_point<ch::system_clock> expected{};
    const std::string timestamp = "6/14/2025 18:30:30.349-4";
    auto result = ParseTimestamp(timestamp);
    EXPECT_NE(result, expected);
}

TEST(ParserTest, ParseTimeStamp_InvalidTimeStamp)
{
    ch::time_point<ch::system_clock> expected{};
    const std::string timestamp = "invalid timestamp";
    auto result = ParseTimestamp(timestamp);
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseTimeStamp_PartiallyInvalidTimeStamp)
{
    ch::time_point<ch::system_clock> expected{};
    const std::string timestamp = "6/14/2025 zx18:30:30.3zx49-4";
    auto result = ParseTimestamp(timestamp);
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_SpellHeal)
{
    const CombatEvent result = ParseLine(test_string);
    CombatEvent expected = test_event;
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidLine)
{
    const CombatEvent expected{};
    const std::string test_string = "invalidline";
    const CombatEvent result = ParseLine(test_string);
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidEventType)
{
    CombatEvent result = ParseLine(test_string);
    result.event_type = "SPELL_INVALID";
    CombatEvent expected{};
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidPlayerName)
{
    CombatEvent expected{};
    CombatEvent result = ParseLine(test_string);
    result.player_name = "invalid1234";
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidSourceId)
{
    CombatEvent expected{};
    CombatEvent result = ParseLine(test_string);
    result.source_id = "invalid1234";
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidTargetId)
{
    CombatEvent expected{};
    CombatEvent result = ParseLine(test_string);
    result.target_id = "invalid1234";
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidSourceRaidFlag)
{
    CombatEvent expected{};
    CombatEvent result = ParseLine(test_string);
    result.source_raid_flag = "invalid1234";
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseLine_InvalidSpellName)
{
    CombatEvent expected{};
    CombatEvent result = ParseLine(test_string);
    result.spell_name = "invalid1234";
    EXPECT_EQ(result, expected);
}

/*
struct CombatEvent {
    std::chrono::system_clock::time_point time_stamp;
    std::string event_type; filter out types we want else {}
    std::string name; no numbers or special chars
    std::string source_id; only numbers letters and hyphens
    std::string target_id; only numbers letters and hyphens
    std::string source_raid_flag; only the proper bitmasks
    std::string spell_name; no numbers or special chars
    int spell_id;
 */
