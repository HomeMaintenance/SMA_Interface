#include "SMADevice.h"
#include <iostream>
#include <cassert>
#include <exception>
#include <ModbusRegister.h>

#define INIT_DEVICE_REGISTERS \
    mbReg_deviceInfo(this, 42109), \
    mbReg_serialNumber(this, 30057), \
    mbReg_device_class(this, 30051), \
    mbReg_device_type(this, 30053), \
    mbReg_rebootRegister(this, 40077), \
    mbReg_power(this, 30775, 1, " W"), \
    mbReg_dcWatt(this, 30773, 1, " W"), \
    mbReg_mainsFeedIn(this, 30867, 1, " W"), \
    mbReg_mainsSupply(this, 30865, 1, " W")

#define GENERATE_MB_GET_FUNC(type, mbRegister) \
    type Device::mbRegister(bool force, bool* ret) const { \
        type retval = 0; \
        if(online()){ \
            retval = mbReg_##mbRegister.getValue(force, ret); \
        } \
        return (retval); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void Device::set_##mbRegister(type input, bool* ret){ \
        if(online){ \
            mbReg_##mbRegister.setValue(input, ret); \
        } \
    }


namespace SMA{
    Device::Device(std::string ipAddress, int port):
        mb::Device(ipAddress, port),
        INIT_DEVICE_REGISTERS
    {
        deviceInit();
        return;
    }

    void Device::deviceInit()
    {
        try{
            parseDeviceInfo();
            bool test{false};
            serialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbReg_serialNumber.readRawData(true, &test).data(), 0));
            device_type = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbReg_device_type.readRawData(true, &test).data(), 0));
            device_class = static_cast<DeviceClass>(MODBUS_GET_INT32_FROM_INT16(mbReg_device_class.readRawData(true, &test).data(), 0));
            std::cout << ipAddress << " is device of class " << device_class << " (" <<  deviceClassToString(device_class) << ")" << std::endl;
            setOnline(test);
        }
        catch (std::exception& e){
            std::cerr << e.what() << std::endl;
            setOnline(false);
            disconnect();
        }
        return;
    }

    void Device::parseDeviceInfo()
    {
        std::runtime_error connection_exception("SMADevice "+ipAddress+":"+std::to_string(port)+ " not reachable");
        if(modbus_set_slave(connection, 1) != 0){
            throw connection_exception;
        }
        bool valid{false};
        std::vector<uint16_t> return_value = mbReg_deviceInfo.readRawData(true, &valid);
        if(!valid){
            throw connection_exception;
        }
        slaveId_ = return_value[3];
        physicalSusyId_ = static_cast<unsigned short>(return_value[2]);
        physicalSerialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(return_value.data(), 0));
        if(modbus_set_slave(connection, slaveId_) != 0){
            throw connection_exception;
        }
    }

    unsigned int Device::power(bool force, bool* ret) const
    {
        int temp = 0;
        if(online()){
            temp = mbReg_power.getValue(force, ret);
        }
        if(temp < 0){
            temp = 0;
        }
        return temp;
    }

    unsigned int Device::dcWatt(bool force, bool* ret) const
    {
        int temp = 0;
        if(online()){
            temp = mbReg_dcWatt.getValue(force, ret);
        }
        if(temp < 0)
            temp = 0;
        return temp;
    }

    GENERATE_MB_GET_FUNC(unsigned int, mainsFeedIn);

    GENERATE_MB_GET_FUNC(unsigned int, mainsSupply);

    void Device::reboot(){
        if(online()){
            mb::Register<int> reboot(this,40077);
            reboot.setValue(1146);
            setOnline(false);
            disconnect();
            while(!online()){
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                connect(ipAddress.c_str(), port);
            }
        }
        return;
    }

    void Device::test()
    {
        bool ret_val = false;
        std::cout << "Test output" << std::endl;
        if(online()){
            device_type = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbReg_device_type.readRawData(false, &ret_val).data(),0));
            std::cout << "Model: " << device_type << " ("<< deviceTypeMap.at(device_type) << "), valid: "<< ret_val << std::endl;
        }
        else{
            std::cout << "not online";
        }
        return;
    }

    void Device::testRead(bool* ret /* = nullptr */)
    {
        std::cout << "online start: " << online() << std::endl;
        std::cout << "power: " << power(false,ret) << std::endl;
        std::cout << "dcWatt: " << dcWatt(false,ret) << std::endl;
        std::cout << "mainsFeedIn: " << mainsFeedIn(false,ret) << std::endl;
        std::cout << "mainsSupply: " << mainsSupply(false,ret) << std::endl;
        std::cout << "online end: " << online() << std::endl;
    }
}
