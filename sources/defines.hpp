#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <chrono>
#include <thread>

#define usleep(x) std::this_thread::sleep_for(std::chrono::microseconds(x))

#define GPIO_RED    1 * 32 + 18
#define GPIO_GREEN  1 * 32 + 28
#define GPIO_BLUE   3
#define GPIO_BP     1 * 32 + 16
#define GPIO_QAM    1 * 32 + 19
#define AN_POTAR    "AIN3"
#define TREF        333

#endif /* DEFINES_HPP */
