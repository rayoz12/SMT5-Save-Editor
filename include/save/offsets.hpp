#pragma once

namespace editor::Offsets
{
    const int FirstName = 0x40C;
    const int FirstName2 = 0x904;
    const int FirstName3 = 0x930;
    const int LastName = 0x91C;
    const int FullName = 0x944; // FirstName {space} LastName

    // General
    const int DateSaved = 0x428; // long
    const int GameDifficulty = 0x430;
    const int PlayTime = 0x431; // in seconds (int). It seems this is what's shown in the file select.
    const int PlayTime2 = 0x504; // in seconds (int). It seems this is where the game's stopwatch picks from
    const int Macca = 0x2F70;
    const int Glory = 0x2F88;

    // Items
    const int ItemOffset = 0x33A0; // byte (0 to 255)

    // Nahobino Stats
    // Some of these are what's shown in the file select screen, others may be "Current Stat/Max Stat" and be shared space with rest of demons. (Investigate) 
    const int NahobinoExp = 0x544; // int
    const int NahobinoExp2 = 0x71C; // int
    const int NahobinoExp3 = 0x8F4; // int
    const int NahobinoLevel = 0x54C; // short
    const int NahobinoLevel2 = 0x724; // short. It seems this is the level that's shown in file select?
    const int NahobinoLevel3 = 0x8FC; // short. It seems this is what's shown in party thumbnail.
    const int NahobinoHp = 0x8BC; // short
    const int NahobinoHp2 = 0x8DC; // short
    const int NahobinoHp3 = 0x8F0; // short
    const int NahobinoMp = 0x8BE; // short
    const int NahobinoMp2 = 0x8DE; // short
    const int NahobinoMp3 = 0x8F2; // short
    const int NahobinoStrength = 0x8C0; // short
    const int NahobinoStrength2 = 0x8D0; // short
    const int NahobinoStrength3 = 0x8E0; // short
    const int NahobinoVitality = 0x8C2; // short
    const int NahobinoVitality2 = 0x8D2; // short
    const int NahobinoVitality3 = 0x8E2; // short
    const int NahobinoMagic = 0x8C4; // short
    const int NahobinoMagic2 = 0x8D4; // short
    const int NahobinoMagic3 = 0x8E4; // short
    const int NahobinoAgility = 0x8C6; // short
    const int NahobinoAgility2 = 0x8D6; // short
    const int NahobinoAgility3 = 0x8E6; // short
    const int NahobinoLuck = 0x8C8; // short
    const int NahobinoLuck2 = 0x8D8; // short
    const int NahobinoLuck3 = 0x8E8; // short
    const int NahobinoSkillId = 0x970; // short? +8
} // namespace editor::Offsets
