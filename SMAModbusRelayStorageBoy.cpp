#include <SMAModbusRelayStorageBoy.h>

namespace SMA{
ModbusRelayStorageBoy::ModbusRelayStorageBoy(std::shared_ptr<StorageBoy> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    registerSoc(deviceOut_.get(), static_cast<int>(0 + addressOffset_)),
    registerChargeCurrent(deviceOut_.get(), static_cast<int>(1 + addressOffset_)),
    registerDischargeCurrent(deviceOut_.get(), static_cast<int>(2 + addressOffset_))
{
}

void ModbusRelayStorageBoy::set_soc_register_address(int address)
{
    registerSoc.addr = address;
}

void ModbusRelayStorageBoy::set_chargeCurrent_register_address(int address)
{
    registerChargeCurrent.addr = address;
}

void ModbusRelayStorageBoy::set_dischargeCurrent_register_address(int address)
{
    registerDischargeCurrent.addr = address;
}

void ModbusRelayStorageBoy::storageBoy_update()
{
    bool ret = false;

    if(abs(static_cast<int>(deviceIn->_soc)-static_cast<int>(_soc_old))>1 || first_run)
    {
        registerSoc.setValue(deviceIn->_soc,&ret);
        _soc_old = deviceIn->_soc;
    }

    if(abs(static_cast<int>(deviceIn->_chargeCurrent)-static_cast<int>(_chargeCurrent_old))>3 || first_run)
    {
        registerChargeCurrent.setValue(deviceIn->_chargeCurrent,&ret);
        _chargeCurrent_old = deviceIn->_chargeCurrent;
    }

    if(abs(static_cast<int>(deviceIn->_dischargeCurrent)-static_cast<int>(_dischargeCurrent_old))>3 || first_run)
    {
        registerDischargeCurrent.setValue(deviceIn->_dischargeCurrent,&ret);
        _dischargeCurrent_old = deviceIn->_dischargeCurrent;
    }
}

void ModbusRelayStorageBoy::update()
{
    storageBoy_update();
    if(first_run)
        first_run = false;
}
}
