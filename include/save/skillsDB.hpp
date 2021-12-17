#pragma once

#include <stdint.h>
#include <map>
#include <vector>
#include <string>

namespace editor::save::skills
{
    struct SkillsDBEntry {
        uint16_t id;
        std::string name;
    };

    extern std::map<uint16_t, SkillsDBEntry> skillsDatabase;
    extern std::vector<SkillsDBEntry> skillList;

    class SkillsDB
    {
    private:
        /* data */
    public:
        SkillsDB();

        std::string getName(uint16_t id);
        SkillsDBEntry getEntry(uint16_t id);
    };

} // namespace editor::save::demon


