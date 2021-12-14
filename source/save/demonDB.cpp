#include "save/demonDB.hpp"
#include <iostream>
#include "json.hpp"

namespace editor::save::demon
{
    std::map<uint16_t, DemonDBEntry> database;

    DemonDB::DemonDB() {

        if (database.size() > 0) {
            // No need to initialise
            return;
        }

        FILE* demonFile = fopen("romfs:/data/demons.json", "r");
        if (demonFile == NULL) {
            printf("Failed to open demons.json!\n");
            return;
        }

        int err = fseek(demonFile, 0, SEEK_END);          // Jump to the end of the file
        if (err < 0) {
            fclose(demonFile);
            return;
        }
        long fileLen = ftell(demonFile);
        rewind(demonFile);

        std::string fileStr(fileLen, '\0');
        fread(&fileStr[0], fileLen, 1, demonFile);

        // We should have it loaded in the string now
        using namespace nlohmann;
        if (!json::accept(fileStr)) {
            printf("Invalid JSON for Demons\n");
            printf("File Len: %d\n", fileLen);
            return;
        }
        // printf("Parsing\n");
        json j = json::parse(fileStr, /* callback */ nullptr, /* allow exceptions */ false, /* skip_comments */ true);
        // printf("Adding to db\n");
        for (auto it : j) {
            // printf("JSON: %s, Size: %d\n", it.dump().c_str(), database.size());
            auto id = it["id"].get<uint16_t>();
            DemonDBEntry entry = { id, it["name"].get<std::string>(), it["image"].get<std::string>(), it.value("race", "Unknown") };
            // printf("id: %d, name: %s, image: %s, race: %s, \n", id, entry.name.c_str(), entry.image.c_str(), entry.race.c_str());
            database.insert(std::make_pair(id, entry));
        }
        // printf("Parsed JSON & added to database\n");
        
    }

    std::string DemonDB::getName(uint16_t id) {
        if ( database.find(id) != database.end() ) {
            auto demonEntry = database.at(id);
            return demonEntry.name;
        } else {
            return std::string("#! Unknown please report this as a Github Issue! ID: ") + std::to_string(id);
        }
    }
} // namespace editor::save::demon
