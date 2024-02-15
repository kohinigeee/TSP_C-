#ifndef UTLITY_EXETIMER_HEADER
#define UTLITY_EXETIMER_HEADER

#include <chrono>
#include <iostream>

class ExeTimer {
    private:
        bool isRunning;
    public:
        std::chrono::system_clock::time_point start;
        std::chrono::system_clock::time_point end;

        ExeTimer(std::chrono::system_clock::time_point start) : start(start), isRunning(true) {}

        void stop() {
            if ( !isRunning ) {
                std::cout << "Timer is already stopped" << std::endl;

                exit(2);
                return;
            }

            end = std::chrono::system_clock::now();
            isRunning = false;
        }

        long long elapsedMilliseconds() {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            return duration.count();
        }

        long long elapsedSeconds() {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            return duration.count();
        }
};

ExeTimer startTimer() {
    return ExeTimer(std::chrono::system_clock::now());
}

#endif