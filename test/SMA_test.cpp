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
    myStorageBoy.read_all_registers();
}

void device_test(){
    SMA::Device myDevice("192.168.178.128");
    myDevice.read_all_registers();
}

int main(int argc, char* argv[]){
    Test test;
    test.increment();
    storageBoy_test();
    device_test();
    return 0;
}
