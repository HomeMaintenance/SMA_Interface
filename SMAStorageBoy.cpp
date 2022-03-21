#include "SMAStorageBoy.h"
#include <iostream>

#define INIT_STORAGEBOY_REGISTERS \
    mbReg_soc(this,30845,1," %"), \
    mbReg_dischargeCurrent(this,31395,1," W"), \
    mbReg_chargeCurrent(this,31393,1," W"), \
    mbReg_maxDischargeCurrent(this,40191,1," W"), \
    mbReg_maxChargeCurrent(this,40189,1," W"), \
    mbReg_charged_energy(this,31397,1," Wh"), \
    mbReg_missing_charge(this,31401,1," Wh")

#define GENERATE_MB_GET_FUNC(type, mbRegister) \
    type StorageBoy::get_##mbRegister(bool* ret) const { \
        type retval = 0; \
        retval = mbReg_##mbRegister.getValue(false, ret); \
        return (retval); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void StorageBoy::set_##mbRegister(type input, bool* ret){ \
        mbReg_##mbRegister.setValue(input, ret); \
    }

namespace SMA {

    StorageBoy::StorageBoy(std::string name, std::string ipAddress, int port):
        Device(ipAddress, port),
        BatteryInverter(name),
        INIT_STORAGEBOY_REGISTERS
    {
        storageBoyInit();
    }

    void StorageBoy::storageBoyInit()
    {
        _maxDischargeCurrent = get_maxDischargeCurrent();
        _maxChargeCurrent = get_maxChargeCurrent();
    }

    float StorageBoy::soc(){
        return static_cast<float>(get_soc());
    }

    float StorageBoy::present_discharge(){
        return static_cast<float>(get_dischargeCurrent());
    }

    float StorageBoy::present_charge(){
        return static_cast<float>(get_chargeCurrent());
    }

    float StorageBoy::charged_energy(){
        return static_cast<float>(get_charged_energy());
    }

    float StorageBoy::max_capacity(){
        return charged_energy() * 100.f / soc();
    }

    float StorageBoy::missing_charge(){
        return static_cast<float>(get_missing_charge());
    }

    float StorageBoy::max_charge_rate() const{
        return static_cast<float>(get_maxChargeCurrent());
    }

    float StorageBoy::max_discharge_rate() const{
        return static_cast<float>(get_maxDischargeCurrent());
    }

    bool StorageBoy::online() const {
        return mb::Device::online();
    }

    GENERATE_MB_GET_FUNC(unsigned int, soc);
    GENERATE_MB_GET_FUNC(unsigned int, dischargeCurrent);
    GENERATE_MB_GET_FUNC(unsigned int, chargeCurrent);
    GENERATE_MB_GET_FUNC(unsigned int, maxDischargeCurrent);
    GENERATE_MB_GET_FUNC(unsigned int, maxChargeCurrent);
    GENERATE_MB_GET_FUNC(long long, charged_energy);
    GENERATE_MB_GET_FUNC(long long, missing_charge);

    void StorageBoy::testRead(bool* ret /* = nullptr */)
    {
        std::cout << "online start: " << mb::Device::online() << std::endl;
        std::cout << "power: " << power(ret) << std::endl;
        std::cout << "dcWatt: " << dcWatt(ret) << std::endl;
        std::cout << "mainsFeedIn: " << mainsFeedIn(ret) << std::endl;
        std::cout << "mainsSupply: " << mainsSupply(ret) << std::endl;
        std::cout << "soc: " << soc() << std::endl;
        std::cout << "dischargeCurrent: " << present_discharge() << std::endl;
        std::cout << "chargeCurrent: " << present_charge() << std::endl;
        std::cout << "maxDischargeCurrent: "<< max_discharge_rate() << std::endl;
        std::cout << "maxChargeCurrent: " << max_charge_rate() << std::endl;
        std::cout << "online end: " << mb::Device::online() << std::endl;
    }
}
