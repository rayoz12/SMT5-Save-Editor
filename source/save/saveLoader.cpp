#include "save/saveLoader.hpp"

namespace editor::saveLoader
{
    Result getPreselectedUser(AccountUid& account) {
        Result rc = accountInitialize(AccountServiceType_Application);
        if (R_FAILED(rc)) {
            printf("accountInitialize() failed: 0x%x\n", rc);
            return rc;
        }

        rc = accountGetPreselectedUser(&account);

        if (R_FAILED(rc)) {
            printf("accountGetPreselectedUser() failed: 0x%x\n", rc);
            return rc;
        }

        return 0;
    }

    Result SaveLoader::getAccount(AccountUid& account) {
        // First we'll try to get a preselected user

        // If that fails we'll prompt for the user
        Result rc = getPreselectedUser(account);
        if (R_SUCCEEDED(rc)) {
            return 0;
        }

        // Prompt for user
        PselUiSettings ui;
        rc = pselUiCreate(&ui, PselUiMode::PselUiMode_UserSelector);

        pselUiSetSkipButtonEnabled(&ui, false);
        rc = pselUiShow(&ui, &account);
        if (R_FAILED(rc)) {
            return rc;
        }

        // printf("Selected account: 0x%lx 0x%lx\n", account.uid[1], account.uid[0]);

        selectedAccount = account;
        return 0;
    }

    Result SaveLoader::getSMTVTitleIDSaves(std::vector<std::uint64_t>& titles) {
        Result rc=0;
        FsSaveDataInfoReader reader;
        s64 total_entries=0;
        FsSaveDataInfo info;

        rc = fsOpenSaveDataInfoReader(&reader, FsSaveDataSpaceId_User);//See libnx fs.h.
        if (R_FAILED(rc)) {
            printf("fsOpenSaveDataInfoReader() failed: 0x%x\n", rc);
            return rc;
        }

        //Find the first savedata with FsSaveDataType_SaveData.
        while(1) {
            rc = fsSaveDataInfoReaderRead(&reader, &info, 1, &total_entries);//See libnx fs.h.
            if (R_FAILED(rc) || total_entries==0) break;

            if (info.save_data_type == FsSaveDataType_Account) {//Filter by FsSaveDataType_Account, however note that FsSaveDataSpaceId_User can have non-FsSaveDataType_Account.
                // printf("Application ID: 0x%lu\n", info.application_id);
                // printf("Account ID: 0x%lu 0x%lu\n", info.uid.uid[1], info.uid.uid[0]);
                if (info.application_id == TITLEID_NA) {
                    printf("Found SMT 5 NA\n");
                    titles.push_back(info.application_id);

                }
                else if (info.application_id == TITLEID_EU) {
                    printf("Found SMT 5 EU\n");
                    titles.push_back(info.application_id);
                }
            }
        }

        return 0;
    }

    Result SaveLoader::mountSave(std::string device, uint64_t titleid, AccountUid& account) {
        Result rc = fsdevMountSaveData(device.c_str(), titleid, account);
        if (R_FAILED(rc)) {
            printf("fsdevMountSaveData() failed: 0x%x\n", rc);
            return rc;
        }
        mountedDevice = device;
        return 0;
    }

    // std::vector<std::string> SaveLoader::getSavePaths(std::string device) {


    // }

} // namespace editor::saveLoader