#include "stdafx.h"
#include "Log.h"

namespace Log
{
    Log::Log()
    {
    }

    Log::~Log()
    {
    }

    template <class... Args>
    void Log::Debug(const char* message, Args... args)
    {
        App::ConsolePrintF(message, args...);
    }

    template void Log::Debug<const char*, unsigned short>(
        const char* message,
        const char*,
        unsigned short
    );

    template void Log::Debug<int>(
        const char*,
        int
    );

    template void Log::Debug<const char*>(
        const char*,
        const char*
    );

    template void Log::Debug<float>(
        const char*,
        float
    );
}