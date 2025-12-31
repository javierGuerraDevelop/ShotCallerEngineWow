#ifndef SHOTCALLERCPP_SPELLDB_H
#define SHOTCALLERCPP_SPELLDB_H

#include <array>
#include <chrono>
#include <string>
#include <string_view>

constexpr std::array<std::string, 45> valid_events{};

constexpr std::array<std::pair<int, std::string_view>, 12> identifying_spells{ {
    { 48743, "Death Knight" },   // Death's Advance
    { 198013, "Demon Hunter" },  // Eye Beam
    { 1126, "Druid" },           // Mark of the Wild
    { 364342, "Evoker" },        // Blessing of the Bronze (Evoker buff)
    { 5384, "Hunter" },          // Feign Death
    { 1459, "Mage" },            // Arcane Intellect
    { 116670, "Monk" },          // Vivify
    { 19750, "Paladin" },        // Flash of Light
    { 21562, "Priest" },         // Power Word: Fortitude
    { 1784, "Rogue" },           // Stealth
    { 10613, "Shaman" },         // Windfury Totem
    { 6673, "Warrior" }          // Battle Shout
} };

constexpr std::string_view get_class(int spell_id)
{
    for (const auto& [id, class_name] : identifying_spells) {
        if (id == spell_id)
            return class_name;
    }

    return "";
}

constexpr std::array<std::string_view, 48> ignorable_events{
    "SWING_DAMAGE",
    "SWING_MISSED",
    "RANGE_DAMAGE",
    "RANGE_MISSED",
    "SPELL_AURA_APPLIED",
    "SPELL_AURA_APPLIED_DOSE",
    "SPELL_AURA_BROKEN",
    "SPELL_AURA_BROKEN_SPELL",
    "SPELL_AURA_REFRESH",
    "SPELL_AURA_REMOVED",
    "SPELL_AURA_REMOVED_DOSE",
    "SPELL_CAST_FAILED",
    "SPELL_CAST_START",
    "SPELL_CREATE",
    "SPELL_DAMAGE",
    "SPELL_DISPEL_FAILED",
    "SPELL_HEAL",
    "SPELL_HEAL_ABSORBED",
    "SPELL_INSTAKILL",
    "SPELL_INTERRUPT",
    "SPELL_LEECH",
    "SPELL_MISSED",
    "SPELL_RESURRECT",
    "SPELL_STOLEN",
    "SPELL_SUMMON",
    "SPELL_EMPOWER_START",
    "SPELL_EMPOWER_END",
    "SPELL_EMPOWER_INTERRUPT",
    "SPELL_PERIODIC_DAMAGE",
    "SPELL_PERIODIC_DRAIN",
    "SPELL_PERIODIC_ENERGIZE",
    "SPELL_PERIODIC_HEAL",
    "SPELL_PERIODIC_LEECH",
    "SPELL_PERIODIC_MISSED",
    "SPELL_BUILDING_DAMAGE",
    "SPELL_BUILDING_HEAL",
    "ENVIRONMENTAL_DAMAGE",
    "DAMAGE_SHIELD",
    "DAMAGE_SHIELD_MISSED",
    "DAMAGE_SPLIT",
    "ENCHANT_APPLIED",
    "ENCHANT_REMOVED",
    "PARTY_KILL",
    "UNIT_DIED",
    "UNIT_DESTROYED",
    "UNIT_DISSIPATES",
    "DURABILITY_DAMAGE",
    "DURABILITY_DAMAGE_ALL",
};

constexpr bool is_ignorable_event(std::string_view event)
{
    for (const auto& item : ignorable_events) {
        if (event == item)
            return true;
    }

    return false;
}

const std::array<std::tuple<std::string_view, int, std::chrono::seconds>, 15> interrupt_data{ {
    { "Death Knight", 47528, std::chrono::seconds{ 15 } },   // Mind Freeze
    { "Demon Hunter", 183752, std::chrono::seconds{ 15 } },  // Disrupt
    { "Druid", 78675, std::chrono::seconds{ 60 } },          // Druid (Moonkin)
    { "Druid", 106839, std::chrono::seconds{ 15 } },         // Skull Bash (Main kick)
    { "Evoker", 351338, std::chrono::seconds{ 20 } },        // Quell
    { "Hunter", 187707, std::chrono::seconds{ 15 } },        // Muzzle
    { "Mage", 2139, std::chrono::seconds{ 24 } },            // Counterspell
    { "Monk", 116705, std::chrono::seconds{ 15 } },          // Spear Hand Strike
    { "Paladin", 96231, std::chrono::seconds{ 15 } },        // Rebuke
    { "Priest", 15487, std::chrono::seconds{ 45 } },         // Silence
    { "Rogue", 1766, std::chrono::seconds{ 15 } },           // Kick
    { "Shaman", 57994, std::chrono::seconds{ 12 } },         // Wind Shear
    { "Warlock", 19647, std::chrono::seconds{ 24 } },        // Spell Lock (Pet)
    { "Warrior", 6552, std::chrono::seconds{ 15 } }          // Pummel
} };

constexpr int GetInterruptId(std::string_view player_class)
{
    for (const auto& [class_name, interrupt_id, interrupt_cd] : interrupt_data) {
        if (player_class == class_name)
            return interrupt_id;
    }

    return {};
}

constexpr std::chrono::seconds GetInterruptCd(std::string_view player_class)
{
    for (const auto& [class_name, interrupt_id, interrupt_cd] : interrupt_data) {
        if (player_class == class_name)
            return interrupt_cd;
    }

    return {};
}

#endif  // SHOTCALLERCPP_SPELLDB_H
