#include <iostream>
#include <fstream>
#include <string>


class ADC
{
public:
    ADC(std::string device);
    ~ADC();

    static void InitCapeADC();

    int read() const;

private:
    static const std::string CapeADC_Path;
    int value;
    std::string dev;
};

