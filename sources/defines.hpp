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
#define TREF_CORH   163
#define TREF_CORL   55

#define TREFH       333-173
#define TREFL       333-133

#define TRIT_A   "1000" //8
#define TRIT_B   "0100" //4
#define TRIT_C   "0010" //2
#define TRIT_D   "0001" //1

#define TRIT_1   "100"
#define TRIT_2   "010"
#define TRIT_3   "001"


#define TRIT_SEQ    "0111"
#define TRIT_SEQ2   "111"

#define REPETITIONS 10

#endif /* DEFINES_HPP */
