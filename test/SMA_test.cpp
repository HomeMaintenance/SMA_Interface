#include <iostream>
#include <SMALIB.h>

class Test{
public:
    Test(){
        int testVal = 5;
        val = &testVal;
    }
    void increment() const {
        (*val)++;
    }
    int getVal() const {
        return *val;
    }
private:
    int* val = nullptr;
};

void storageBoy_test(){
    SMA::StorageBoy myStorageBoy("192.168.178.113");
    auto soc = myStorageBoy.soc();
    auto present_discharge = myStorageBoy.present_discharge();
    auto present_charge = myStorageBoy.present_charge();
    auto charged_energy = myStorageBoy.charged_energy();
    auto max_capacity = myStorageBoy.max_capacity();
    auto missing_charge = myStorageBoy.missing_charge();
    auto max_charge_rate = myStorageBoy.max_charge_rate();
    auto max_discharge_rate = myStorageBoy.max_discharge_rate();
    return;
}

void device_test(){
    SMA::Device myDevice("192.168.178.128");
    auto dcWatt = myDevice.get_dcWatt();
    auto mainsFeedIn = myDevice.get_mainsFeedIn();
    auto mainsSupply = myDevice.get_mainsSupply();
    auto power = myDevice.get_power();
    return;
}

void mains_test(){
    std::shared_ptr<SMA::Device> myDevice = std::make_shared<SMA::Device>("192.168.178.128");
    SMA::ModbusRelayMains mainsRelay(myDevice, nullptr, 0);
    auto result = mainsRelay.mains_update();
    return;
}

int main(int argc, char* argv[]){
    Test test;
    test.increment();
    storageBoy_test();
    device_test();
    mains_test();
    return 0;
}
