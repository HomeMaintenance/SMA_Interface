#include <SMAModbusRelayMains.h>

#define RELAY_VALUE(val_name, ret) i.second.setValue(#val_name,ret)
#define READ_VALUE(out_var_name, val_name) unsigned int (out_var_name)_temp = static_cast<unsigned int>(mbDeviceIn->val_name)

namespace SMA{
ModbusRelayMains::ModbusRelayMains(std::weak_ptr<Device> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_)
{
    if(deviceOut_ != nullptr){
        registerMainsFeedIn = new mb::Register<unsigned int>(deviceOut_.get(), static_cast<int>(0 + addressOffset_));
        registerMainsSupply = new mb::Register<unsigned int>(deviceOut_.get(), static_cast<int>(1 + addressOffset_));
    }
}

ModbusRelayMains::~ModbusRelayMains(){
    delete registerMainsFeedIn;
    registerMainsFeedIn = nullptr;
    delete registerMainsSupply;
    registerMainsSupply = nullptr;
}

void ModbusRelayMains::set_MainsFeedIn_register_address(int address)
{
    registerMainsFeedIn->addr = address;
}

void ModbusRelayMains::set_MainsSuppy_register_address(int address)
{
    registerMainsSupply->addr = address;
}

uint8_t ModbusRelayMains::mains_update()
{
    auto read_device = deviceIn.lock();
    assert(read_device && "read_device must not be nullptr");


    bool ret1 = false;
    bool ret1_1 = false;
    auto mains_feedIn = read_device->mainsFeedIn(false, &ret1);
    if(abs(static_cast<int>(mains_feedIn)-static_cast<int>(_mainsFeedIn_old))>3 || first_run)
    {
        if(registerMainsFeedIn)
            registerMainsFeedIn->setValue(mains_feedIn,&ret1_1);
        _mainsFeedIn_old = mains_feedIn;
    }

    bool ret2 = false;
    bool ret2_1 = false;
    auto mains_supply = read_device->mainsSupply(false, &ret2);
    if(abs(static_cast<int>(mains_supply)-static_cast<int>(_mainsSupply_old))>3 || first_run)
    {
        if(registerMainsSupply)
            registerMainsSupply->setValue(mains_supply,&ret2_1);
        _mainsSupply_old = mains_supply;
    }
    uint8_t result = static_cast<uint8_t>(ret1) << 3 |
        static_cast<uint8_t>(ret1_1) << 2 |
        static_cast<uint8_t>(ret2) << 1 |
        static_cast<uint8_t>(ret2_1);
    return result;
}

void ModbusRelayMains::update(std::string message)
{
    bool ret = mains_update();
    if(ret && first_run)
        first_run = false;
}
}
