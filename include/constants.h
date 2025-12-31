#ifndef SHOTCALLERCPP_SPELLDB_H
#define SHOTCALLERCPP_SPELLDB_H

#include <array>
#include <chrono>
#include <string_view>

namespace Constants {

inline constexpr std::array<std::pair<int, std::string_view>, 12> identifying_spells{ {
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

constexpr std::string_view GetClassFromIdentifyingSpells(int spell_id)
{
    for (const auto& [id, class_name] : identifying_spells) {
        if (id == spell_id)
            return class_name;
    }

    return "";
}

inline constexpr std::array<std::string_view, 40> valid_events{
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
    "SPELL_INSTAKILL",
    "SPELL_INTERRUPT",
    "SPELL_LEECH",
    "SPELL_MISSED",
    "SPELL_STOLEN",
    "SPELL_SUMMON",
    "SPELL_EMPOWER_START",
    "SPELL_EMPOWER_END",
    "SPELL_EMPOWER_INTERRUPT",
    "SPELL_PERIODIC_DAMAGE",
    "SPELL_PERIODIC_DRAIN",
    "SPELL_PERIODIC_ENERGIZE",
    "SPELL_PERIODIC_LEECH",
    "SPELL_PERIODIC_MISSED",
    "SPELL_BUILDING_DAMAGE",
    "SPELL_BUILDING_HEAL",
    "ENVIRONMENTAL_DAMAGE",
    "DAMAGE_SHIELD",
    "DAMAGE_SHIELD_MISSED",
    "DAMAGE_SPLIT",
    "PARTY_KILL",
    "UNIT_DIED",
    "UNIT_DESTROYED",
    "UNIT_DISSIPATES",
};

constexpr bool IsIgnorableEvent(std::string_view event)
{
    for (const auto& item : valid_events) {
        if (event == item)
            return false;
    }

    return true;
}

inline constexpr std::array<std::tuple<std::string_view, int, std::chrono::seconds>, 15>
    interrupt_data{ {
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

enum CcEnum : size_t {
    CLASS_NAME = 0,
    SPELL_NAME = 1,
    SPELL_ID = 2,
    SPELL_CD = 3,
};

inline constexpr std::array<
    std::tuple<std::string_view, std::string_view, int, std::chrono::seconds>, 31>
    crowd_control_data{
        { { "Death Knight", "Blinding Sleet", 207127, std::chrono::seconds{ 60 } },
          { "Death Knight", "Gorefiend's Grasp", 207167, std::chrono::seconds{ 90 } },
          { "Demon Hunter", "Chaos Nova", 179057, std::chrono::seconds{ 60 } },
          { "Demon Hunter", "Sigil of Silence", 202138, std::chrono::seconds{ 90 } },
          { "Demon Hunter", "Sigil of Misery", 207684, std::chrono::seconds{ 90 } },
          { "Demon Hunter", "Sigil of Chains", 204598, std::chrono::seconds{ 90 } },
          { "Druid", "Mass Entanglement", 102359, std::chrono::seconds{ 30 } },
          { "Druid", "Ursol's Vortex", 102793, std::chrono::seconds{ 60 } },
          { "Druid", "Typhoon", 132469, std::chrono::seconds{ 30 } },
          { "Evoker", "Landslide", 371900, std::chrono::seconds{ 90 } },
          { "Evoker", "Deep Breath", 358269, std::chrono::seconds{ 120 } },
          { "Evoker", "Tail Swipe", 368725, std::chrono::seconds{ 90 } },
          { "Hunter", "Binding Shot", 109248, std::chrono::seconds{ 45 } },
          { "Mage", "Frost Nova", 122, std::chrono::seconds{ 30 } },
          { "Mage", "Dragon's Breath", 31661, std::chrono::seconds{ 45 } },
          { "Mage", "Ring of Frost", 113724, std::chrono::seconds{ 45 } },
          { "Mage", "Blast Wave", 157981, std::chrono::seconds{ 30 } },
          { "Monk", "Leg Sweep", 119381, std::chrono::seconds{ 60 } },
          { "Monk", "Ring of Peace", 116844, std::chrono::seconds{ 60 } },
          { "Paladin", "Blinding Light", 105421, std::chrono::seconds{ 90 } },
          { "Priest", "Psychic Scream", 8122, std::chrono::seconds{ 60 } },
          { "Shaman", "Capacitor Totem", 192058, std::chrono::seconds{ 60 } },
          { "Shaman", "Earthgrab Totem", 51485, std::chrono::seconds{ 30 } },
          { "Shaman", "Thunderstorm", 51490, std::chrono::seconds{ 45 } },
          { "Shaman", "Sundering", 197214, std::chrono::seconds{ 40 } },
          { "Warlock", "Howl of Terror", 5484, std::chrono::seconds{ 45 } },
          { "Warlock", "Shadowfury", 30283, std::chrono::seconds{ 60 } },
          { "Warrior", "Intimidating Shout", 5246, std::chrono::seconds{ 90 } },
          { "Warrior", "Shockwave", 46968, std::chrono::seconds{ 40 } } }
    };

constexpr std::chrono::seconds GetCcCd(int id)
{
    for (const auto& [class_name, spell_name, spell_id, spell_cd] : crowd_control_data) {
        if (id == spell_id)
            return spell_cd;
    }

    return {};
}

constexpr std::string_view GetCcName(int id)
{
    for (const auto& [class_name, spell_name, spell_id, spell_cd] : crowd_control_data) {
        if (id == spell_id)
            return spell_name;
    }

    return {};
}
}  // namespace Constants

#endif  // SHOTCALLERCPP_SPELLDB_H
