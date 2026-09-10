#pragma once

namespace Log
{
    class Log
    {
    public:
        Log();
        ~Log();

        template <class... Args>
        void Debug(const char* message, Args... args);
    };
}