#pragma once
#include <chrono>

namespace RT
{
    class Timer
    {
    public:
        Timer() : m_Start(std::chrono::steady_clock::now()) {}

        double Peek() const
        {
            return std::chrono::duration<double, std::chrono::minutes::period>(
                std::chrono::steady_clock::now() - m_Start).count();
        }

    private:
        std::chrono::steady_clock::time_point m_Start;
    };
}
