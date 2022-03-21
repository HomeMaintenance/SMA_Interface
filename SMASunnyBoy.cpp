#include "SMASunnyBoy.h"

namespace SMA{

SunnyBoy::SunnyBoy(std::string name, std::string ipAddress, int port):
    Device(ipAddress, port),
    PowerSource(name)
{

}

float SunnyBoy::get_available_power() const{
    return power();
}

void SunnyBoy::set_available_power(float value){

}

Json::Value SunnyBoy::toJson() const{
    Json::Value jsonData = PowerSource::toJson();
    jsonData["online"] = online();
    return jsonData;
}
}
