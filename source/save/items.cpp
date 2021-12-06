
#include "save/items.hpp"
#include "util/state.hpp"

namespace editor::save
{
    ItemManager::ItemManager() {
        loadItems();
        
        for (auto &&item : itemList) {
            if (item.isUsed) {
                usableItemList.push_back(item);
            }
        }
        
    }

    void ItemManager::parseSave() {
        int counter = 0;
        for (int i = 0x33A1; i <= 0x347C; i++) {
            auto item = itemList[counter];
            uint8_t count = saveInterface.getByte(i);
            if (count > 0) {
                usedItems[item.id] = {item, count};
            }

            counter++;
        }
        
    }

    void ItemManager::updateSave() {
        for (auto &&playerItem : usedItems) {
            auto usedItem = playerItem.second;
            saveInterface.putByte(usedItem.item.offset, usedItem.count);
        }        
    }

    void ItemManager::addItem(UsedItem item) {
        if ( usedItems.find(item.item.id) == usedItems.end() ) {
            usedItems[item.item.id] = item;
        } else {
            usedItems[item.item.id].count++;
        }
    }

    void ItemManager::loadItems() {
        itemList.push_back({"Life Stone",           0x33A1,0,true});
        itemList.push_back({"Chakra Drop",          0x33A2,1,true});
        itemList.push_back({"Chakra Pot",           0x33A3,2,true});
        itemList.push_back({"Bead",                 0x33A4,3,true});
        itemList.push_back({"Bead Chain",           0x33A5,4,true});
        itemList.push_back({"Soma",                 0x33A6,5,true});
        itemList.push_back({"Revival Bead",         0x33A7,6,true});
        itemList.push_back({"Balm of Life",         0x33A8,7,true});
        itemList.push_back({"Arita Soda",           0x33A9,8,true});
        itemList.push_back({"Amrita Shower",        0x33AA,9,true});
        itemList.push_back({"Medicine",             0x33AB,10,true});
        itemList.push_back({"Ox Bezoar",            0x33AC,11,true});
        itemList.push_back({"Ambrosia",             0x33AD,12,true});
        itemList.push_back({"Muscle Drink",         0x33AE,13,true});
        itemList.push_back({"Unused Item 15",       0x33AF,14,false});
        itemList.push_back({"Unused Item 16",       0x33B0,15,false});
        itemList.push_back({"Fire Shard",           0x33B1,16,true});
        itemList.push_back({"Ice Shard",            0x33B2,17,true});
        itemList.push_back({"Elec Shard",           0x33B3,18,true});
        itemList.push_back({"Force Shard",          0x33B4,19,true});
        itemList.push_back({"Light Shard",          0x33B5,20,true});
        itemList.push_back({"Dark Shard",           0x33B6,21,true});
        itemList.push_back({"Fire Gem",             0x33B7,22,true});
        itemList.push_back({"Ice Gem",              0x33B8,23,true});
        itemList.push_back({"Elec Gem",             0x33B9,24,true});
        itemList.push_back({"Force Gem",            0x33BA,25,true});
        itemList.push_back({"Light Gem",            0x33BB,26,true});
        itemList.push_back({"Dark Gem",             0x33BC,27,true});
        itemList.push_back({"Unused Item 29",       0x33BD,28,false});
        itemList.push_back({"Unused Item 30",       0x33BE,29,false});
        itemList.push_back({"Unused Item 31",       0x33BF,30,false});
        itemList.push_back({"Unused Item 32",       0x33C0,31,false});
        itemList.push_back({"Unused Item 33",       0x33C1,32,false});
        itemList.push_back({"Unused Item 34",       0x33C2,33,false});
        itemList.push_back({"Unused Item 35",       0x33C3,34,false});
        itemList.push_back({"Unused Item 36",       0x33C4,35,false});
        itemList.push_back({"Poison Gem",           0x33C5,36,true});
        itemList.push_back({"Sleep Gem",            0x33C6,37,true});
        itemList.push_back({"Confusionn Gem",       0x33C7,38,true});
        itemList.push_back({"Mirage Gem",           0x33C8,39,true});
        itemList.push_back({"Seal Gem",             0x33C9,40,true});
        itemList.push_back({"Charm Gem",            0x33CA,41,true});
        itemList.push_back({"Charge Gem",           0x33CB,42,true});
        itemList.push_back({"Concentrate Gem",      0x33CC,43,true});
        itemList.push_back({"Critical Gem",         0x33CD,44,true});
        itemList.push_back({"Spirit Drain Gem",     0x33CE,45,true});
        itemList.push_back({"Life Drain Gem",       0x33CF,46,true});
        itemList.push_back({"Unused Item 48",       0x33D0,47,false});
        itemList.push_back({"Unused Item 49",       0x33D1,48,false});
        itemList.push_back({"Purge Charm",          0x33D2,49,true});
        itemList.push_back({"Dispel Charm",         0x33D3,50,true});
        itemList.push_back({"Attack Mirror",        0x33D4,51,true});
        itemList.push_back({"Magic Mirror",         0x33D5,52,true});
        itemList.push_back({"Unused Item 54",       0x33D6,53,false});
        itemList.push_back({"Spyglass",             0x33D7,54,true});
        itemList.push_back({"Unused Item 56",       0x33D8,55,false});
        itemList.push_back({"Unused Item 57",       0x33D9,56,false});
        itemList.push_back({"Unused Item 58",       0x33DA,57,false});
        itemList.push_back({"Unused Item 59",       0x33DB,58,false});
        itemList.push_back({"Whittled Goat",        0x33DC,59,true});
        itemList.push_back({"Smoke Ball",           0x33DD,60,true});
        itemList.push_back({"Phys Dampener",        0x33DE,61,true});
        itemList.push_back({"Fire Dampener",        0x33DF,62,true});
        itemList.push_back({"Ice Dampener",         0x33E0,63,true});
        itemList.push_back({"Elec Dampener",        0x33E1,64,true});
        itemList.push_back({"Force Dampener",       0x33E2,65,true});
        itemList.push_back({"Light Dampener",       0x33E3,66,true});
        itemList.push_back({"Dark Dampener",        0x33E4,67,true});
        itemList.push_back({"Unused Item 69",       0x33E5,68,false});
        itemList.push_back({"Return Pillar",        0x33E6,69,true});
        itemList.push_back({"Repulse Bell",         0x33E7,70,true});
        itemList.push_back({"Unused Item 72",       0x33E8,71,false});
        itemList.push_back({"Unused Item 73",       0x33E9,72,false});
        itemList.push_back({"Unused Item 74",       0x33EA,73,false});
        itemList.push_back({"Unused Item 75",       0x33EB,74,false});
        itemList.push_back({"Unused Item 76",       0x33EC,75,false});
        itemList.push_back({"Unused Item 77",       0x33ED,76,false});
        itemList.push_back({"Unused Item 78",       0x33EE,77,false});
        itemList.push_back({"Unused Item 79",       0x33EF,78,false});
        itemList.push_back({"Unused Item 80",       0x33F0,79,false});
        itemList.push_back({"Unused Item 81",       0x33F1,80,false});
        itemList.push_back({"Gospel",               0x33F2,81,true});
        itemList.push_back({"Grimoire",             0x33F3,82,true});
        itemList.push_back({"Health Balm",          0x33F4,83,true});
        itemList.push_back({"Stamina Bal",          0x33F5,84,true});
        itemList.push_back({"Strength Balm",        0x33F6,85,true});
        itemList.push_back({"Magic Balm",           0x33F7,86,true});
        itemList.push_back({"Vitality Balm",        0x33F8,87,true});
        itemList.push_back({"Agility Balm",         0x33F9,88,true});
        itemList.push_back({"Luck Balm",            0x33FA,89,true});
        itemList.push_back({"Health Incense",       0x33FB,90,true});
        itemList.push_back({"Stamina Incense",      0x33FC,91,true});
        itemList.push_back({"Strength Incense",     0x33FD,92,true});
        itemList.push_back({"Magic Incense",        0x33FE,93,true});
        itemList.push_back({"Vitality Incense",     0x33FF,94,true});
        itemList.push_back({"Agility Incense",      0x3400,95,true});
        itemList.push_back({"Luck Incense",         0x3401,96,true});
        itemList.push_back({"Battle Sutra",         0x3402,97,true});
        itemList.push_back({"Fire Sutra",           0x3403,98,true});
        itemList.push_back({"Ice Sutra",            0x3404,99,true});
        itemList.push_back({"Elec Sutra",           0x3405,100,true});
        itemList.push_back({"Force Sutra",          0x3406,101,true});
        itemList.push_back({"Light Sutra",          0x3407,102,true});
        itemList.push_back({"Dark Sutra",           0x3408,103,true});
        itemList.push_back({"Destruction Sutra",    0x3409,104,true});
        itemList.push_back({"Healing Sutra",        0x340A,105,true});
        itemList.push_back({"Aiding Sutra",         0x340B,106,true});
        itemList.push_back({"Calamity Sutra",       0x340C,107,true});
        itemList.push_back({"Small Glory Crystal",  0x340D,108,true});
        itemList.push_back({"Large Glory Crystal",  0x340E,109,true});
        itemList.push_back({"Unused Item",          0x340F,110,false});
        itemList.push_back({"Unused Item",          0x3410,111,false});
        itemList.push_back({"Unused Item",          0x3411,112,false});
        itemList.push_back({"Unused Item",          0x3412,113,false});
        itemList.push_back({"Unused Item",          0x3413,114,false});
        itemList.push_back({"Unused Item",          0x3414,115,false});
        itemList.push_back({"Unused Item",          0x3415,116,false});
        itemList.push_back({"Unused Item",          0x3416,117,false});
        itemList.push_back({"Unused Item",          0x3417,118,false});
        itemList.push_back({"Unused Item",          0x3418,119,false});
        itemList.push_back({"Unused Item",          0x3419,120,false});
        itemList.push_back({"Unused Item",          0x341A,121,false});
        itemList.push_back({"Unused Item",          0x341B,122,false});
        itemList.push_back({"Unused Item",          0x341C,123,false});
        itemList.push_back({"Unused Item",          0x341D,124,false});
        itemList.push_back({"Unused Item",          0x341E,125,false});
        itemList.push_back({"Unused Item",          0x341F,126,false});
        itemList.push_back({"Unused Item",          0x3420,127,false});
        itemList.push_back({"Unused Item",          0x3421,128,false});
        itemList.push_back({"Unused Item",          0x3422,129,false});
        itemList.push_back({"Unused Item",          0x3423,130,false});
        itemList.push_back({"Unused Item",          0x3424,131,false});
        itemList.push_back({"Unused Item",          0x3425,132,false});
        itemList.push_back({"Unused Item",          0x3426,133,false});
        itemList.push_back({"Unused Item",          0x3427,134,false});
        itemList.push_back({"Unused Item",          0x3428,135,false});
        itemList.push_back({"Unused Item",          0x3429,136,false});
        itemList.push_back({"Unused Item",          0x342A,137,false});
        itemList.push_back({"Unused Item",          0x342B,138,false});
        itemList.push_back({"Unused Item",          0x342C,139,false});
        itemList.push_back({"Unused Item",          0x342D,140,false});
        itemList.push_back({"Unused Item",          0x342E,141,false});
        itemList.push_back({"Unused Item",          0x342F,142,false});
        itemList.push_back({"Unused Item",          0x3430,143,false});
        itemList.push_back({"Unused Item",          0x3431,144,false});
        itemList.push_back({"Unused Item",          0x3432,145,false});
        itemList.push_back({"Unused Item",          0x3433,146,false});
        itemList.push_back({"Unused Item",          0x3434,147,false});
        itemList.push_back({"Unused Item",          0x3435,148,false});
        itemList.push_back({"Unused Item",          0x3436,149,false});
        itemList.push_back({"Unused Item",          0x3437,150,false});
        itemList.push_back({"Unused Item",          0x3438,151,false});
        itemList.push_back({"Unused Item",          0x3439,152,false});
        itemList.push_back({"Unused Item",          0x343A,153,false});
        itemList.push_back({"Unused Item",          0x343B,154,false});
        itemList.push_back({"Unused Item",          0x343C,155,false});
        itemList.push_back({"Unused Item",          0x343D,156,false});
        itemList.push_back({"Unused Item",          0x343E,157,false});
        itemList.push_back({"Unused Item",          0x343F,158,false});
        itemList.push_back({"Unused Item",          0x3440,159,false});
        itemList.push_back({"Unused Item",          0x3441,160,false});
        itemList.push_back({"Unused Item",          0x3442,161,false});
        itemList.push_back({"Unused Item",          0x3443,162,false});
        itemList.push_back({"Unused Item",          0x3444,163,false});
        itemList.push_back({"Unused Item",          0x3445,164,false});
        itemList.push_back({"Unused Item",          0x3446,165,false});
        itemList.push_back({"Unused Item",          0x3447,166,false});
        itemList.push_back({"Unused Item",          0x3448,167,false});
        itemList.push_back({"Unused Item",          0x3449,168,false});
        itemList.push_back({"Unused Item",          0x344A,169,false});
        itemList.push_back({"Unused Item",          0x344B,170,false});
        itemList.push_back({"Unused Item",          0x344C,171,false});
        itemList.push_back({"Unused Item",          0x344D,172,false});
        itemList.push_back({"Unused Item",          0x344E,173,false});
        itemList.push_back({"Unused Item",          0x344F,174,false});
        itemList.push_back({"Unused Item",          0x3450,175,false});
        itemList.push_back({"Unused Item",          0x3451,176,false});
        itemList.push_back({"Unused Item",          0x3452,177,false});
        itemList.push_back({"Unused Item",          0x3453,178,false});
        itemList.push_back({"Unused Item",          0x3454,179,false});
        itemList.push_back({"Unused Item",          0x3455,180,false});
        itemList.push_back({"Unused Item",          0x3456,181,false});
        itemList.push_back({"Unused Item",          0x3457,182,false});
        itemList.push_back({"Unused Item",          0x3458,183,false});
        itemList.push_back({"Unused Item",          0x3459,184,false});
        itemList.push_back({"Unused Item",          0x345A,185,false});
        itemList.push_back({"Unused Item",          0x345B,186,false});
        itemList.push_back({"Unused Item",          0x345C,187,false});
        itemList.push_back({"Unused Item",          0x345D,188,false});
        itemList.push_back({"Unused Item",          0x345E,189,false});
        itemList.push_back({"Unused Item",          0x345F,190,false});
        itemList.push_back({"Unused Item",          0x3460,191,false});
        itemList.push_back({"Unused Item",          0x3461,192,false});
        itemList.push_back({"Unused Item",          0x3462,193,false});
        itemList.push_back({"Unused Item",          0x3463,194,false});
        itemList.push_back({"Unused Item",          0x3464,195,false});
        itemList.push_back({"Unused Item",          0x3465,196,false});
        itemList.push_back({"Unused Item",          0x3466,197,false});
        itemList.push_back({"Unused Item",          0x3467,198,false});
        itemList.push_back({"Unused Item",          0x3468,199,false});
        itemList.push_back({"Unused Item",          0x3469,200,false});
        itemList.push_back({"Unused Item",          0x346A,201,false});
        itemList.push_back({"Unused Item",          0x346B,202,false});
        itemList.push_back({"Unused Item",          0x346C,203,false});
        itemList.push_back({"Unused Item",          0x346D,204,false});
        itemList.push_back({"Unused Item",          0x346E,205,false});
        itemList.push_back({"Unused Item",          0x346F,206,false});
        itemList.push_back({"Unused Item",          0x3470,207,false});
        itemList.push_back({"Unused Item",          0x3471,208,false});
        itemList.push_back({"Unused Item",          0x3472,209,false});
        itemList.push_back({"Unused Item",          0x3473,210,false});
        itemList.push_back({"Unused Item",          0x3474,211,false});
        itemList.push_back({"Unused Item",          0x3475,212,false});
        itemList.push_back({"Unused Item",          0x3476,213,false});
        itemList.push_back({"Unused Item",          0x3477,214,false});
        itemList.push_back({"Unused Item",          0x3478,215,false});
        itemList.push_back({"Unused Item",          0x3479,216,false});
        itemList.push_back({"Unused Item",          0x347A,217,false});
        itemList.push_back({"Unused Item",          0x347B,218,false});
        itemList.push_back({"Unused Item",          0x347C,219,false});

    }

} // namespace editor::save
