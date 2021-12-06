#include "util/keyboard.hpp"

#include <switch.h>
#include <stdio.h>
#include <limits>

unsigned long maxValue = 0;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

SwkbdTextCheckResult validate_name(char* tmp_string, size_t tmp_string_size) {
    pu::String string(tmp_string);
    if (string.length() > 8) {
        strncpy(tmp_string, "Max 8 Characters", 64);
        return SwkbdTextCheckResult_Bad;
    }

    return SwkbdTextCheckResult_OK;
}

SwkbdTextCheckResult validate_number(char* tmp_string, size_t tmp_string_size) {
    std::string string(tmp_string);
    
    if (!is_number(string)) {
        strncpy(tmp_string, "Only Numbers are allowed!", 64);
        return SwkbdTextCheckResult_Bad;
    }
    
    unsigned long number = std::stoul(string);
    if (number > maxValue) {
        std::string errorStr("Please enter values between 0 - " + std::to_string(maxValue));
        strncpy(tmp_string, errorStr.c_str(), 64);
        return SwkbdTextCheckResult_Bad;
    }
    return SwkbdTextCheckResult_OK;
}

namespace editor::util::keyboard
{   

    Keyboard::Keyboard() {

    }

    pu::String Keyboard::inputString(pu::String currentValue) {
        SwkbdConfig kbd;
        char tmpoutstr[64] = {0};

        Result rc = makeKeyboard(kbd);
        if (R_FAILED(rc)) {
            printf("Failed to Create Keyboard 0x%x\n", rc);
            return currentValue;
        }
        swkbdConfigSetInitialText(&kbd, currentValue.AsUTF8().c_str());

        std::string headerStr("Enter a name");

        swkbdConfigSetHeaderText(&kbd, headerStr.c_str());
        maxValue = maxValue;
        swkbdConfigSetTextCheckCallback(&kbd, validate_name);
        
        rc = swkbdShow(&kbd, tmpoutstr, sizeof(tmpoutstr));
        if (R_FAILED(rc)) {
            swkbdClose(&kbd);
            return currentValue;
        }
        swkbdClose(&kbd);
        pu::String resultStr(tmpoutstr);
        return resultStr;
    }

    uint64_t Keyboard::inputNumber(uint64_t currentValue, uint64_t maxValueIn) {
        SwkbdConfig kbd;
        char tmpoutstr[64] = {0};

        Result rc = makeKeyboard(kbd);
        if (R_FAILED(rc)) {
            printf("Failed to Create Keyboard 0x%x\n", rc);
            return currentValue;
        }
        swkbdConfigSetInitialText(&kbd, std::to_string(currentValue).c_str());

        std::string headerStr("Enter number between 0-" + std::to_string(maxValueIn));

        swkbdConfigSetHeaderText(&kbd, headerStr.c_str());
        maxValue = maxValue;
        swkbdConfigSetTextCheckCallback(&kbd, validate_number);
        
        rc = swkbdShow(&kbd, tmpoutstr, sizeof(tmpoutstr));
        if (R_FAILED(rc)) {
            swkbdClose(&kbd);
            return currentValue;
        }
        swkbdClose(&kbd);
        std::string numberStr(tmpoutstr);
        return std::stoul(numberStr);

    }

    uint8_t Keyboard::inputByte(uint8_t currentValue) {
        return inputNumber(currentValue, 255);
    }

    uint16_t Keyboard::input2Bytes(uint16_t currentValue) {
        return inputNumber(currentValue, std::numeric_limits<uint16_t>::max());
    }

    uint32_t Keyboard::input4Bytes(uint32_t currentValue) {
        return inputNumber(currentValue, std::numeric_limits<uint32_t>::max());
    }

    uint64_t Keyboard::input8Bytes(uint64_t currentValue) {
        return inputNumber(currentValue, std::numeric_limits<uint64_t>::max());
    }

    Result Keyboard::makeKeyboard(SwkbdConfig& kbd) {
        Result rc = swkbdCreate(&kbd, 0);
        if (R_FAILED(rc)) {
            return rc; 
        }

        swkbdConfigMakePresetDefault(&kbd);
        return rc;
    }

} // namespace editor::util::keyboard
