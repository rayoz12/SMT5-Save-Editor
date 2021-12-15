#pragma once

#include <stdint.h>
#include <map>
#include <string>

namespace editor::save::demon
{


    struct DemonDBEntry {
        uint16_t id;
        std::string name;
        std::string image;
        std::string race;
    };

    extern std::map<uint16_t, DemonDBEntry> database;

    class DemonDB
    {
    private:
        /* data */
    public:
        DemonDB();

        std::string getName(uint16_t id);
        std::string getRace(uint16_t id);
    };

} // namespace editor::save::demon


