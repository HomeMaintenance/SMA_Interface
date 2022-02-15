#include <iostream>
#include "SMAStorageBoy.h"

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

int main(int argc, char* argv[]){
    Test test;
    test.increment();
    SMA::StorageBoy myStorageBoy("192.168.178.113");
    myStorageBoy.read_all_registers();
    return 0;
}
