#pragma once
#include <string>
#include <map>

namespace SMA{

    enum DeviceClass{
        AllDevices = 8000,
        PVInverter,
        WindPowerInverter,
        BatteryInverter,
        Load,
        SensorTechnologyGeneral,
        EnergyMeter,
        CommunicationProduct
    };

    std::string deviceClassToString(const DeviceClass& dc);

    const std::map<unsigned int,std::string> deviceTypeMap{
        {9067, "Sunny Tripower STP 10000TL-10"},
        {9068, "Sunny Tripower STP 12000TL-10"},
        {9069, "Sunny Tripower STP 15000TL-10"},
        {9070, "Sunny Tripower STP 17000TL-10"},
        {9074, "Sunny Boy SB 3000TL-21"},
        {9075, "Sunny Boy SB 4000TL-21"},
        {9076, "Sunny Boy SB 5000TL-21"},
        {9098, "Sunny Tripower STP 5000TL-20"},
        {9099, "Sunny Tripower STP 6000TL-20"},
        {9100, "Sunny Tripower STP 7000TL-20"},
        {9101, "Sunny Tripower STP 8000TL-10"},
        {9102, "Sunny Tripower STP 9000TL-20"},
        {9103, "Sunny Tripower STP 8000TL-20"},
        {9162, "Sunny Boy SB 3500TL-JP-22"},
        {9164, "Sunny Boy SB 4500TL-JP-22"},
        {9165, "Sunny Boy SB 3600TL-21"},
        {9181, "Sunny Tripower STP 20000TLEE-10"},
        {9182, "Sunny Tripower STP 15000TLEE-10"},
        {9184, "Sunny Boy SB 2500TLST-21"},
        {9185, "Sunny Boy SB 3000TLST-21"},
        {9194, "Sunny Tripower STP 12000TL-US-10"},
        {9195, "Sunny Tripower STP 15000TL-US-10"},
        {9196, "Sunny Tripower STP 20000TL-US-10"},
        {9197, "Sunny Tripower STP 24000TL-US-10"},
        {9198, "Sunny Boy SB 3000TL-US-22"},
        {9199, "Sunny Boy SB 3800TL-US-22"},
        {9200, "Sunny Boy SB 4000TL-US-22"},
        {9201, "Sunny Boy SB 5000TL-US-22"},
        {9222, "Sunny Tripower STP 10000TLEE-JP-10"},
        {9223, "Sunny Island SI6.0H-11"},
        {9224, "Sunny Island SI8.0H-11"},
        {9225, "Sunny Boy SB 5000SE-10"},
        {9226, "Sunny Boy SB 3600SE-10"},
        {9271, "Sunny Tripower STP 20000TLEE-JP-11"},
        {9272, "Sunny Tripower STP 10000TLEE-JP-11"},
        {9274, "Sunny Boy SB 6000TL-US-22"},
        {9275, "Sunny Boy SB 7000TL-US-22"},
        {9278, "Sunny Island SI3.0M-11"},
        {9279, "Sunny Island SI4.4M-11"},
        {9281, "Sunny Tripower STP 10000TL-20"},
        {9282, "Sunny Tripower STP 11000TL-20"},
        {9283, "Sunny Tripower STP 12000TL-20"},
        {9284, "Sunny Tripower STP 20000TL-30"},
        {9285, "Sunny Tripower STP 25000TL-30"},
        {9293, "Sunny Boy SB 7700TL-US-22"},
        {9301, "Sunny Boy SB1.5-1VL-40"},
        {9302, "Sunny Boy SB2.5-1VL-40"},
        {9304, "Sunny Boy SB5.0-1SP-US-40"},
        {9305, "Sunny Boy SB6.0-1SP-US-40"},
        {9306, "Sunny Boy SB7.7-1SP-US-40"},
        {9310, "Sunny Tripower STP 30000TL-US-10"},
        {9311, "Sunny Tripower STP 25000TL-JP-30"},
        {9319, "Sunny Boy SB3.0-1AV-40"},
        {9320, "Sunny Boy SB3.6-1AV-40"},
        {9321, "Sunny Boy SB4.0-1AV-40"},
        {9322, "Sunny Boy SB5.0-1AV-40"},
        {9326, "Sunny Boy Storage SBS2.5-1VL-40"},
        {9328, "Sunny Boy SB3.0-1SP-US-40"},
        {9329, "Sunny Boy SB3.8-1SP-US-40"},
        {9330, "Sunny Boy SB7.0-1SP-US-40"},
        {9332, "Sunny Island SI4.4M-12"},
        {9333, "Sunny Island SI6.0H-12"},
        {9334, "Sunny Island SI8.0H-12"},
        {9336, "Sunny Tripower STP 15000TL-30"},
        {9338, "Sunny Tripower STP 50-40"},
        {9339, "Sunny Tripower STP 50-US-40"},
        {9340, "Sunny Tripower STP 50-JP-40"},
        {9354, "Sunny Tripower STP 24500TL-JP-30"}
    };
}
