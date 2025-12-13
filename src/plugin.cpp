#include <vector>
#include <string_view>
#include "plugin.h"

static std::vector<wchar_t> Utf8ToUtf16(std::string_view str)
{
    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, 0, 0);
    if (requiredSize > 0)
    {
        std::vector<wchar_t> buffer(requiredSize);
        MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, &buffer[0], requiredSize);
        return buffer;
    }
    return {};
}

static bool cbEncode(ExpressionValue* result, int argc, const ExpressionValue* argv, void* userdata)
{
    // Encode the string as a sequence of hex bytes. The input strings are always utf-8 encoded.
    auto str = std::string_view(argv[0].string.ptr);
    auto encoding = argv[1].string.ptr;
    std::string encoded;
    if (_stricmp(encoding, "utf-8") == 0 || _stricmp(encoding, "utf8") == 0)
    {
        encoded.reserve(str.size() * 2);
        for (size_t i = 0; i < str.size(); i++)
        {
            char tmp[3];
            sprintf_s(tmp, "%02X", (uint8_t)str[i]);
            encoded += tmp;
        }
    }
    else if (_stricmp(encoding, "utf-16") == 0 || _stricmp(encoding, "utf16") == 0)
    {
        auto utf16 = Utf8ToUtf16(str);
        encoded.reserve(utf16.size() * 4);
        for (size_t i = 0; i < utf16.size(); i++)
        {
            char tmp[5];
            sprintf_s(tmp, "%02X%02X", (uint8_t)(utf16[i] & 0xFF), (uint8_t)((utf16[i] >> 8) & 0xFF));
            encoded += tmp;
        }
    }
    else
    {
        return false; // Unknown encoding
    }

    // Set the result
    result->type = ValueTypeString;
    auto ptr = (char*)BridgeAlloc(encoded.size() + 1);
    strcpy_s(ptr, encoded.size() + 1, encoded.c_str());
    result->string.ptr = ptr;
    result->string.isOwner = true;

    return true;
}

// Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    dprintf("pluginInit(pluginHandle: %d)\n", pluginHandle);

    ValueType args[] = { ValueTypeString, ValueTypeString };
    _plugin_registerexprfunctionex(pluginHandle, "encode", ValueTypeString, args, _countof(args), cbEncode, nullptr);

    // Return false to cancel loading the plugin.
    return true;
}

// Deinitialize your plugin data here.
// NOTE: you are responsible for gracefully closing your GUI
// This function is not executed on the GUI thread, so you might need
// to use WaitForSingleObject or similar to wait for everything to close.
void pluginStop()
{
}

// Do GUI/Menu related things here.
// This code runs on the GUI thread: GetCurrentThreadId() == GuiGetMainThreadId()
// You can get the HWND using GuiGetWindowHandle()
void pluginSetup()
{
}
