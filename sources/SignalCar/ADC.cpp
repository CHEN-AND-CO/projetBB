#include "ADC.hpp"

const std::string ADC::CapeADC_Path = "/sys/devices/ocp.3/helper.14/";

ADC::ADC(std::string device) : value(NULL), dev(device)
{
    
}

ADC::~ADC()
{
    
}

int ADC::read() const {
    std::ifstream _dev(ADC::CapeADC_Path + dev);

    if (!_dev)
    {
        std::cerr << "[CapeADC] Cannot open ADC system file\n\tMake sure Cape devices are correctly initialized beforehand.\n";
        return -1;
    }
    else
    {
        std::string val;
        _dev >> val;
        return std::stoi(val);
    }

    _dev.close();
}


