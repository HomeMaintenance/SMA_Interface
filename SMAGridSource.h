#pragma once
#include "SMADevice.h"
#include <PowerSource.h>

namespace SMA{
    class GridSource: public Device, public PowerSource
    {
    public:
        GridSource(std::string ipAddress, std::string name = "SMAGridSource", int port = 502);
        ~GridSource();
        virtual float get_available_power() const override;
    };
}
