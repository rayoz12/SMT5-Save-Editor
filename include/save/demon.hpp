#pragma once

#include <stdint.h>
#include <vector>

#include "save/saveInterface.hpp"

namespace editor::save
{
    
class Demon {
public:

    SaveInterface saveInterface;

    Demon(long offset);

    void save();

    long selfOffset;

    // Stats
	uint16_t hp;
	uint16_t mp;
    uint16_t base_strength;
    uint16_t base_vitality;
    uint16_t base_magic;
    uint16_t base_agility;
    uint16_t base_luck;
    uint16_t hp_item;
    uint16_t mp_item;
    uint16_t strength_item;
    uint16_t vitality_item;
    uint16_t magic_item;
    uint16_t agility_item;
    uint16_t luck_item;
    uint16_t hp_combined;
    uint16_t mp_combined;
    uint16_t strength_combined;
    uint16_t vitality_combined;
    uint16_t magic_combined;
    uint16_t agility_combined;
    uint16_t luck_combined;
    
    // General
    // padding[28]; +28 bytes
    uint32_t experience;
    // padding[6]; +6 bytes
    uint16_t level;
    uint16_t id;

    std::vector<uint16_t> skills;
    
    // Skills
    // // padding[8]; +8 bytes
    // uint16_t skill_1;
    // // padding[6]; +6 bytes
    // uint16_t skill_2;
    // // padding[6]; +6 bytes
    // uint16_t skill_3;
    // // padding[6]; +6 bytes
    // uint16_t skill_4;
    // // padding[6]; +6 bytes
    // uint16_t skill_5;
    // // padding[6]; +6 bytes
    // uint16_t skill_6;
    // // padding[6]; +6 bytes
    // uint16_t skill_7;
    // // padding[6]; +6 bytes
    // uint16_t skill_8;
    
    
    // Skill Potential
    // padding[146]; +146 bytes
    int16_t potential_physical;
    int16_t potential_fire;
    int16_t potential_ice;
    int16_t potential_electric;
    int16_t potential_force;
    int16_t potential_light;
    int16_t potential_dark;
    int16_t potential_almighty;
    int16_t potential_ailment;
    int16_t potential_healing;
    int16_t potential_support;
    
};

} // namespace editor::save