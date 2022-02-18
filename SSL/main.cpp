#include "curl.h"
#include "hook.h"

bool bHasReset = false; // temporary fix.

void Main()
{
    if (!bHasReset)
    {
        fdelete(GetCobaltPath() + "\\logs.txt");
        bHasReset = !bHasReset;
        fcreate(GetCobaltPath() + "\\logs.txt");
    }
    std::string b = ", ";
    WriteToLog(ConstToStr("Settings: ") + FloatToStr(ver) + b + BoolToStr(bIsProd) + b + BoolToStr(bIsS13) + b + BoolToStr(bWriteLogsToFile) + b + BoolToStr(bHasReset) + b + BoolToStr(INGAME) + b + BoolToStr(PROCESSEVENTHOOK) + b + BoolToStr(bIsHybrid));
    WriteToLog("Redirecting streams..");
    AllocConsole();
    FILE* a;
    freopen_s(&a, ENC("CONIN$"), "w", stdin);
#ifdef SENDLOGSTOCONSOLE
    freopen_s(&a, ENC("CONOUT$"), "w", stdout);
    freopen_s(&a, ENC("CONOUT$"), "w", stderr);
#endif
#ifdef WRITELOGSTOFILE
#ifndef SENDLOGSTOCONSOLE // It doesn't send to console and logs atm.
    freopen_s(&a, ENC("logs.txt"), "w", stdout); // Writes processevent (logs) to file.
#endif
#endif
    Curl::Curl();
    Hooking::Hook((void*)CurlEasyOptP, Curl::CurlHook, (void**)&_curl_easy_setopt, HookMethod);
    const char* ascii = ENC(R"()");
    Log(ascii);
    Log("\nLaunching CobaltV2!"); //(" + ver);
    Log(ConstToStr("Redirecting to ") + FNhost, true, true);
}
