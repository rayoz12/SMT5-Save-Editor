#include "save/demon.hpp"

namespace editor::save
{
    // Parse a demon from an HP(!) offset
    Demon::Demon(long offset) {
        selfOffset = offset;


        // I could make all of this stuff into an array and a loop to cut down on lines
        // but it's simple and clearer like this.

        // We have read every second byte
        long statOffset = offset;
        hp =                saveInterface.get2Bytes(offset + (0 * 2)); 
        mp =                saveInterface.get2Bytes(offset + (1 * 2)); 
        base_strength =     saveInterface.get2Bytes(offset + (2 * 2)); 
        base_vitality =     saveInterface.get2Bytes(offset + (3 * 2));
        base_magic =        saveInterface.get2Bytes(offset + (4 * 2));
        base_agility =      saveInterface.get2Bytes(offset + (5 * 2));
        base_luck =         saveInterface.get2Bytes(offset + (6 * 2));
        hp_item =           saveInterface.get2Bytes(offset + (7 * 2));
        mp_item =           saveInterface.get2Bytes(offset + (8 * 2));
        strength_item =     saveInterface.get2Bytes(offset + (9 * 2));
        vitality_item =     saveInterface.get2Bytes(offset + (10 * 2));
        magic_item =        saveInterface.get2Bytes(offset + (11 * 2));
        agility_item =      saveInterface.get2Bytes(offset + (12 * 2));
        luck_item =         saveInterface.get2Bytes(offset + (13 * 2));
        hp_combined =       saveInterface.get2Bytes(offset + (16 * 2));
        mp_combined =       saveInterface.get2Bytes(offset + (17 * 2));
        strength_combined = saveInterface.get2Bytes(offset + (18 * 2));
        vitality_combined = saveInterface.get2Bytes(offset + (19 * 2));
        magic_combined =    saveInterface.get2Bytes(offset + (20 * 2));
        agility_combined =  saveInterface.get2Bytes(offset + (21 * 2));
        luck_combined =     saveInterface.get2Bytes(offset + (22 * 2));

        long generalOffset = offset + 70; // +0x46
        experience = saveInterface.get4Bytes(generalOffset);
        // padding[6]; +6 bytes
        level = saveInterface.get2Bytes(generalOffset + 10);
        id = saveInterface.get2Bytes(generalOffset + 12);

        long skillsOffset = offset + 92; // +0x5C
        for (int i = 0; i < 8; i++) {
            skills.push_back(saveInterface.get2Bytes(skillsOffset + (i * 8)));
        }

        long potentialOffset = offset + 286; // +0x128
        potential_physical  = saveInterface.get2BytesSigned(potentialOffset);
        potential_fire      = saveInterface.get2BytesSigned(potentialOffset + (1 * 2));
        potential_ice       = saveInterface.get2BytesSigned(potentialOffset + (2 * 2));
        potential_electric  = saveInterface.get2BytesSigned(potentialOffset + (3 * 2));
        potential_force     = saveInterface.get2BytesSigned(potentialOffset + (4 * 2));
        potential_light     = saveInterface.get2BytesSigned(potentialOffset + (5 * 2));
        potential_dark      = saveInterface.get2BytesSigned(potentialOffset + (6 * 2));
        potential_almighty  = saveInterface.get2BytesSigned(potentialOffset + (7 * 2));
        potential_ailment   = saveInterface.get2BytesSigned(potentialOffset + (8 * 2));
        potential_healing   = saveInterface.get2BytesSigned(potentialOffset + (9 * 2));
        potential_support   = saveInterface.get2BytesSigned(potentialOffset + (10 * 2));

        name = demonDB.getName(id);
        race = demonDB.getRace(id);

    }

    void Demon::save() {
        // We have read every second byte
        long statOffset = selfOffset;
        saveInterface.put2Bytes(statOffset + (0  * 2), hp); 
        saveInterface.put2Bytes(statOffset + (1  * 2), mp); 
        saveInterface.put2Bytes(statOffset + (2  * 2), base_strength); 
        saveInterface.put2Bytes(statOffset + (3  * 2), base_vitality);
        saveInterface.put2Bytes(statOffset + (4  * 2), base_magic);
        saveInterface.put2Bytes(statOffset + (5  * 2), base_agility);
        saveInterface.put2Bytes(statOffset + (6  * 2), base_luck);
        saveInterface.put2Bytes(statOffset + (7  * 2), hp_item);
        saveInterface.put2Bytes(statOffset + (8  * 2), mp_item);
        saveInterface.put2Bytes(statOffset + (9  * 2), strength_item);
        saveInterface.put2Bytes(statOffset + (10 * 2), vitality_item);
        saveInterface.put2Bytes(statOffset + (11 * 2), magic_item);
        saveInterface.put2Bytes(statOffset + (12 * 2), agility_item);
        saveInterface.put2Bytes(statOffset + (13 * 2), luck_item);
        saveInterface.put2Bytes(statOffset + (16 * 2), hp_combined);
        saveInterface.put2Bytes(statOffset + (17 * 2), mp_combined);
        saveInterface.put2Bytes(statOffset + (18 * 2), strength_combined);
        saveInterface.put2Bytes(statOffset + (19 * 2), vitality_combined);
        saveInterface.put2Bytes(statOffset + (20 * 2), magic_combined);
        saveInterface.put2Bytes(statOffset + (21 * 2), agility_combined);
        saveInterface.put2Bytes(statOffset + (22 * 2), luck_combined);

        long generalOffset = selfOffset + 70; // +0x46
        saveInterface.put4Bytes(generalOffset, experience);
        // padding[6]; +6 bytes
        saveInterface.put2Bytes(generalOffset + 10, level);
        saveInterface.put2Bytes(generalOffset + 12, id);

        long skillsOffset = selfOffset + 92; // +0x5C
        for (int i = 0; i < 8; i++) {
            saveInterface.put2Bytes(skillsOffset + (i * 8), skills[i]);
        }

        long potentialOffset = selfOffset + 286; // +0x128

        saveInterface.put2BytesSigned(potentialOffset, potential_physical);
        saveInterface.put2BytesSigned(potentialOffset + (1 * 2), potential_fire);
        saveInterface.put2BytesSigned(potentialOffset + (2 * 2), potential_ice);
        saveInterface.put2BytesSigned(potentialOffset + (3 * 2), potential_electric);
        saveInterface.put2BytesSigned(potentialOffset + (4 * 2), potential_force);
        saveInterface.put2BytesSigned(potentialOffset + (5 * 2), potential_light);
        saveInterface.put2BytesSigned(potentialOffset + (6 * 2), potential_dark);
        saveInterface.put2BytesSigned(potentialOffset + (7 * 2), potential_almighty);
        saveInterface.put2BytesSigned(potentialOffset + (8 * 2), potential_ailment);
        saveInterface.put2BytesSigned(potentialOffset + (9 * 2), potential_healing);
        saveInterface.put2BytesSigned(potentialOffset + (10 * 2), potential_support);
    }
} // namespace editor::save
