#pragma once

#include <string>
#include <vector>
#include <map>

#include "save/saveInterface.hpp"

namespace editor::save {
    const int ItemOffset = 0x33A1;

    struct Item {
        std::string name;
        long offset;
        int id;
        bool isUsed;
    };

    struct UsedItem {
        Item item;
        uint8_t count;
    };

    /**
     * @brief This manages the items in a save file.
     * You give it a decrypted save buffer and you can:
     *  - Get items in there
     *  - Add Items
     *  - Modify Items
     */
    class ItemManager {

    public:
        ItemManager();
        
        /**
         * @brief Updates this classes state from the save globally loaded
         * 
         */
        void parseSave();
        
        // Commit changes t the save
        void updateSave();

        // Add an item to the player
        void addItem(UsedItem item);

        // Load items from list
        void loadItems();

        SaveInterface saveInterface;
        
        // The raw Item list with offsets
        std::vector<Item> itemList;
        std::vector<Item> usableItemList;
        // The items held by the player (count > 0)
        std::map<int, UsedItem> usedItems;
    };
    
}