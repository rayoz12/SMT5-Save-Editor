#pragma once

namespace editor::Offsets
{
    const int FirstName = 1036;
    const int FirstName2 = 2308;
    const int FirstName3 = 2352;
    const int LastName = 2332;
    const int FullName = 2372; // FirstName {space} LastName

    // General
    const int DateSaved = 1064; // long
    const int GameDifficulty = 1072;
    const int PlayTime = 1073; // in seconds (int). It seems this is what's shown in the file select.
    const int PlayTime2 = 1284; // in seconds (int). It seems this is where the game's stopwatch picks from
    const int Macca = 12144;
    const int Glory = 12168;

    // Items
    const int ItemOffset = 13216; // byte (0 to 255)

    // Nahobino Stats
    // Some of these are what's shown in the file select screen, others may be "Current Stat/Max Stat" and be shared space with rest of demons. (Investigate) 
    const int NahobinoExp = 1348; // int
    const int NahobinoExp2 = 1820; // int
    const int NahobinoExp3 = 2292; // int
    const int NahobinoLevel = 1356; // short
    const int NahobinoLevel2 = 1828; // short. It seems this is the level that's shown in file select?
    const int NahobinoLevel3 = 2300; // short. It seems this is what's shown in party thumbnail.
    const int NahobinoHp = 2236; // short
    const int NahobinoHp2 = 2268; // short
    const int NahobinoHp3 = 2288; // short
    const int NahobinoMp = 2238; // short
    const int NahobinoMp2 = 2270; // short
    const int NahobinoMp3 = 2290; // short
    const int NahobinoStrength = 2240; // short
    const int NahobinoStrength2 = 2256; // short
    const int NahobinoStrength3 = 2272; // short
    const int NahobinoVitality = 2242; // short
    const int NahobinoVitality2 = 2258; // short
    const int NahobinoVitality3 = 2274; // short
    const int NahobinoMagic = 2244; // short
    const int NahobinoMagic2 = 2260; // short
    const int NahobinoMagic3 = 2276; // short
    const int NahobinoAgility = 2246; // short
    const int NahobinoAgility2 = 2262; // short
    const int NahobinoAgility3 = 2278; // short
    const int NahobinoLuck = 2248; // short
    const int NahobinoLuck2 = 2264; // short
    const int NahobinoLuck3 = 2280; // short
    const int NahobinoSkillId = 2416; // short? +8
} // namespace editor::Offsets
