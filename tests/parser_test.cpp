#include "parser.h"

#include <gtest/gtest.h>

namespace ch = std::chrono;

TEST(ParserTest, ParseTimeStamp_ValidTimeStamp) {
    ch::time_point<ch::system_clock> expected{};
    const std::string timestamp = "6/14/2025 18:30:30.349-4";
    auto result = ParseTimestamp(timestamp);
    EXPECT_NE(result, expected);
}

TEST(ParserTest, ParseTimeStamp_InvalidTimeStamp) {
    ch::time_point<ch::system_clock> expected{};
    const std::string timestamp = "invalid timestamp";
    auto result = ParseTimestamp(timestamp);
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ParseTimeStamp_PartiallyInvalidTimeStamp) {
    ch::time_point<ch::system_clock> expected{};
    const std::string timestamp = "6/14/2025 zx18:30:30.3zx49-4";
    auto result = ParseTimestamp(timestamp);
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, ValidEventType) {
    const std::string test_string =
        R"(6/14/2025 18:01:18.304-4  SPELL_CAST_START,Creature-0-4218-2661-9671-218671-0000CDF11C,"Venture Co. Pyromaniac",0xa48,0x0,0000000000000000,nil,0x80000000,0x80000000,434505,"Guzzle Cinderbrew",0x1)";
    const CombatEvent expected = {ParseTimestamp("6/14/2025 18:01:18.304-4"),
                                  "SPELL_CAST_START",
                                  "Venture Co. Pyromaniac",
                                  "Creature-0-4218-2661-9671-218671-0000CDF11C",
                                  "0000000000000000",
                                  "0xa48",
                                  "Guzzle Cinderbrew",
                                  434505};
    const CombatEvent result = ParseLine(test_string);
    EXPECT_EQ(result, expected);
}

TEST(ParserTest, InvalidEventType) {
    const std::string test_string =
        R"(6/14/2025 18:30:30.349-4  SPELL_PERIODIC_HEAL,Player-3676-0CD71E8D,"Bigchalupa-Area52-US",0x511,0x0,Player-76-0BED3564,"Darthdemonic-Sargeras-US",0x512,0x0,156322,"Eternal Flame",0x6,Player-76-0BED3564,0000000000000000,7574108,10997049,13305,97197,39210,117,300,27243,0,2423075,2500000,0,2660.46,-5010.41,2335,3.2456,676,18846,18846,0,0,nil)";
    const CombatEvent expected{};
    const CombatEvent result = ParseLine(test_string);
    EXPECT_EQ(result, expected);
}
