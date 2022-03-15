#include "SMADeviceTypes.h"

namespace SMA{
    std::string deviceClassToString(const DeviceClass& dc){
        switch(static_cast<DeviceClass>(dc)){
            case DeviceClass::AllDevices: return "AllDevices"; break;
            case DeviceClass::PVInverter: return "PVInverter"; break;
            case DeviceClass::WindPowerInverter: return "WindPowerInverter"; break;
            case DeviceClass::BatteryInverter: return "BatteryInverter"; break;
            case DeviceClass::Load: return "Load"; break;
            case DeviceClass::SensorTechnologyGeneral: return "SensorTechnologyGeneral"; break;
            case DeviceClass::EnergyMeter: return "EnergyMeter"; break;
            case DeviceClass::CommunicationProduct: return "CommunicationProduct"; break;
            default: return "";
        }
    }
}
