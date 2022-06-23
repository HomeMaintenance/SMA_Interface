#include "SMAGridSource.h"

namespace SMA{
    GridSource::GridSource(std::string ipAddress, std::string name /* = "SMAGridSource" */,  int port /* = 502 */):
        Device(ipAddress, port), PowerSource(name)
    {

    }

    GridSource::~GridSource(){

    }

    float GridSource::get_available_power() const {
        return mainsFeedIn() - mainsSupply();
    }
}
