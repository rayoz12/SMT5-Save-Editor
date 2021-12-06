#pragma once

#include <switch.h>
#include <vector>
#include <string>

namespace editor::saveLoader
{
    /**
     * Class handles acount selection and mounting of the save partition so that we can access it.
     */
    class SaveLoader {
    public:
        /**
         *  Get player account. Get's the default one, if there is more than 
         *  one a prompt is shown for the user to select their user
         */
        AccountUid getAccount();

        /**
         * This gets the title ID's of the saves on the device. 
         * There are 2 versions of the game (NA, EUR) so it's possible for
         * a user to have both save datas
         */
        std::vector<std::string> getSMTVTitleIDSaves();


    };
} // namespace editor::saveLoader
