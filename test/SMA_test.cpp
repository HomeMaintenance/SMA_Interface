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
    std::cout << "soc: " << soc << std::endl;
    auto present_discharge = myStorageBoy.present_discharge();
    std::cout << "present_discharge: " << present_discharge << std::endl;
    auto present_charge = myStorageBoy.present_charge();
    std::cout << "present_charge: " << present_charge << std::endl;
    auto charged_energy = myStorageBoy.charged_energy();
    std::cout << "charged_energy: " << charged_energy << std::endl;
    auto max_capacity = myStorageBoy.max_capacity();
    std::cout << "max_capacity: " << max_capacity << std::endl;
    auto missing_charge = myStorageBoy.missing_charge();
    std::cout << "missing_charge: " << missing_charge << std::endl;
    auto max_charge_rate = myStorageBoy.max_charge_rate();
    std::cout << "max_charge_rate: " << max_charge_rate << std::endl;
    auto max_discharge_rate = myStorageBoy.max_discharge_rate();
    std::cout << "max_discharge_rate: " << max_discharge_rate << std::endl;
    std::cout << "-----------------" << std::endl;
    return;
}

void device_test(){
    SMA::Device myDevice("192.168.178.128");
    auto dcWatt = myDevice.get_dcWatt();
    std::cout << "dcWatt: " << dcWatt << std::endl;
    auto mainsFeedIn = myDevice.get_mainsFeedIn();
    std::cout << "mainsFeedIn: " << mainsFeedIn << std::endl;
    auto mainsSupply = myDevice.get_mainsSupply();
    std::cout << "mainsSupply: " << mainsSupply << std::endl;
    auto power = myDevice.get_power();
    std::cout << "power: " << power << std::endl;
    std::cout << "-----------------" << std::endl;
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
