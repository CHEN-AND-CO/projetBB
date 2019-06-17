#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <chrono>
#include <thread>

#define usleep(x) std::this_thread::sleep_for(std::chrono::microseconds(x))

#define GPIO_RED    1 * 32 + 18
#define GPIO_GREEN  1 * 32 + 28
#define GPIO_BLUE   3
#define GPIO_BP     1 * 32 + 16

#endif /* DEFINES_HPP */