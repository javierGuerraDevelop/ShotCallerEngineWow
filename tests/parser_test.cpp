#include "parser.h"

#include <gtest/gtest.h>

namespace ch = std::chrono;

TEST(ParserTest, ValidTimeStamp)
{
    ch::time_point<ch::system_clock> default_constructed{};

    const std::string timestamp = "6/14/2025 18:30:30.349-4";
    auto result = parse_timestamp(timestamp);

    EXPECT_NE(result, default_constructed);
}

TEST(ParserTest, InvalidTimeStamp)
{
    ch::time_point<ch::system_clock> default_constructed{};

    const std::string timestamp = "invalid timestamp";
    auto result = parse_timestamp(timestamp);

    EXPECT_EQ(result, default_constructed);
}

TEST(ParserTest, PartiallyInvalidTimeStamp)
{
    ch::time_point<ch::system_clock> default_constructed{};

    const std::string timestamp = "6/14/2025 zx18:30:30.3zx49-4";
    auto result = parse_timestamp(timestamp);

    EXPECT_EQ(result, default_constructed);
}
