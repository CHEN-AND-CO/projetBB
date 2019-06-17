#include "GPIO.hpp"

const std::string GPIO::IN = "in";
const std::string GPIO::OUT = "out"; 

GPIO::GPIO(int port, std::string mode): port{port}, export_state{false}, mode{mode} {
    export_state = init(port);

    if(export_state){
        if(mode.compare("") && !setMode(mode)) std::cerr << "Error : Failed to set GPIO port " << port << " to " << mode << " mode !" << "\n";
    }else{
        std::cerr << "Error : Failed to open GPIO port " << port << "\n";
    }
}

bool GPIO::init(int port){
    std::ofstream out{ GPIO_PATH "/export" };

    if(out.bad()) return false;

    out << port;
    out.flush();

    return true;
}

bool GPIO::setMode(std::string mode){
    if(!mode.compare(GPIO::IN) || !mode.compare(GPIO::OUT)){
        std::ofstream out{ GPIO_PATH "/gpio" + std::to_string(port) + "/direction" };
        
        if(out.bad()) return false;

        out << mode;
        out.flush();
        this->mode = mode;

        return true;
    }else{
        return false;
    }
}

bool GPIO::set(bool state){
    if(!export_state){
        std::cerr << "Error : GPIO Port " << port << " not initialised !" << "\n";
    }else if(!mode.compare("")){
        std::cerr << "Error : No I/O mode set for GPIO " << port << "\n";
    }else if(!mode.compare(GPIO::IN)){
        std::cerr << "Error : GPIO Port " << port << " is configured in INPUT mode !" << "\n";
    }else{
        std::ofstream out{ GPIO_PATH "/gpio" + std::to_string(port) + "/value" };

        if(!out.bad()){
            out << ((state)?1:0);
            out.flush();

            return true;
        }
    }

    return false;
}

int GPIO::get(){
    int state = -1;

    if(!export_state){
        std::cerr << "Error : GPIO Port " << port << " not initialised !" << "\n";
    }else if(!mode.compare("")){
        std::cerr << "Error : No I/O mode set for GPIO " << port << "\n";

        return -2;
    }else{
        std::ifstream in{ GPIO_PATH "/gpio" + std::to_string(port) + "/value" };
        
        if(!in.bad()) {
            in >> state;
        }
    }

    return state;
}

bool GPIO::close(){
    if(!export_state){
        std::cerr << "Error : GPIO Port " << port << " not initialised !" << "\n";
    }else{
        set(false);
        std::ofstream out{ GPIO_PATH "/unexport" };

        if(!out.bad()){
            out << port;
            out.flush();

            export_state = false;

            return true;
        }
    }

    return false;
}