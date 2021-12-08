#pragma once

#include <switch.h>
#include <vector>
#include <string>

namespace editor::saveLoader
{
    const uint64_t TITLEID_NA = 0x010063B012DC6000;
    const uint64_t TITLEID_EU = 0x0100B870126CE000;

    /**
     * Class handles acount selection and mounting of the save partition so that we can access it.
     */
    class SaveLoader {
    public:
        /**
         *  Get player account. Get's the default one, if there is more than 
         *  one a prompt is shown for the user to select their user
         */
        Result getAccount(AccountUid& account);

        /**
         * This gets the title ID's of the saves on the device. 
         * There are 2 versions of the game (NA, EUR) so it's possible for
         * a user to have both save datas
         */
        Result getSMTVTitleIDSaves(std::vector<uint64_t>& titles);

        Result mountSave(std::string device, uint64_t titleid, AccountUid& account);

        std::vector<std::string> getSavePaths(std::string device);

        AccountUid selectedAccount;
        std::string mountedDevice;


    };
} // namespace editor::saveLoader

