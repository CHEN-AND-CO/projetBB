#ifndef GPIO_HPP
#define GPIO_HPP

#include <iostream>
#include <fstream>
#include <string>

#define GPIO_PATH "/sys/class/gpio"

class GPIO {
public:
    GPIO(int port, std::string mode ="");
    ~GPIO(){ if(export_state)close(); }

    bool init(int port);
    bool setMode(std::string mode); 
    std::string getMode() const { return mode; }
    bool set(bool state);
    int get();
    bool close();

    static const std::string IN, OUT;   
private:
    int port;
    bool export_state;
    std::string mode;
};

#endif /* GPIO_HPP */