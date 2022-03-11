#pragma once
#include "SMADevice.h"
#include <PowerSource.h>

namespace SMA{
class SunnyBoy: public Device, public PowerSource{
public:
    explicit SunnyBoy(std::string name, std::string ipAddress, int port = 502);
    virtual ~SunnyBoy() = default;
    virtual float get_available_power() const override;

protected:
    virtual void set_available_power(float value) override;
};
}
