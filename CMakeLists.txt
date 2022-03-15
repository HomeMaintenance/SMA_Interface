cmake_minimum_required(VERSION 3.20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(sma_interface)

include(FetchContent)
FetchContent_Declare(
    ObserverModel
    GIT_REPOSITORY https://github.com/HomeMaintenance/ObserverModel.git
    GIT_TAG main
)

FetchContent_Declare(
    ModbusDevice_Interface
    GIT_REPOSITORY https://github.com/HomeMaintenance/Modbus.git
    GIT_TAG main
)

FetchContent_Declare(
    PowerManagement
    GIT_REPOSITORY https://github.com/HomeMaintenance/PowerManagement.git
    GIT_TAG main
)

FetchContent_Declare(
    mqtt_interface
    GIT_REPOSITORY https://github.com/HomeMaintenance/Mqtt.git
    GIT_TAG main
)

FetchContent_MakeAvailable(ObserverModel ModbusDevice_Interface mqtt_interface PowerManagement)

add_subdirectory(test)

add_library(
    SMADevice
    SMADeviceTypes.h
    SMADevice.h
    SMADevice.cpp
)
target_link_libraries(SMADevice PUBLIC ModbusDevice)
target_include_directories(SMADevice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    SMAStorageBoy
    SMAStorageBoy.h
    SMAStorageBoy.cpp
)
target_link_libraries(SMAStorageBoy PUBLIC SMADevice PowerManagement)

add_library(
    SMASunnyBoy
    SMASunnyBoy.h
    SMASunnyBoy.cpp
)
target_link_libraries(SMASunnyBoy PUBLIC SMADevice PowerManagement)

add_library(
    SMAMqttInterface
    SMAMqttInterface.h
    SMAMqttInterface.cpp
)
target_link_libraries(SMAMqttInterface PUBLIC mqtt)
target_link_libraries(SMAMqttInterface PUBLIC ObserverModel)

add_library(
    SMADeviceMqtt
    SMADeviceMqtt.h
    SMADeviceMqtt.cpp
)
target_link_libraries(SMADeviceMqtt PUBLIC SMADevice)
target_link_libraries(SMADeviceMqtt PUBLIC SMAMqttInterface)

add_library(
    SMAMainsMqtt
    SMAMainsMqtt.h
    SMAMainsMqtt.cpp
)
target_link_libraries(SMAMainsMqtt PUBLIC SMADevice)
target_link_libraries(SMAMainsMqtt PUBLIC SMAMqttInterface)

add_library(
    SMAStorageBoyMqtt
    SMAStorageBoyMqtt.h
    SMAStorageBoyMqtt.cpp
)
target_link_libraries(SMAStorageBoyMqtt PUBLIC SMAStorageBoy)
target_link_libraries(SMAStorageBoyMqtt PUBLIC SMAMqttInterface)

add_library(SMAMqtt INTERFACE)
target_link_libraries(SMAMqtt INTERFACE SMADeviceMqtt SMAMainsMqtt SMAStorageBoyMqtt)

add_library(
    SMAModbusRelayInterface
    SMAModbusRelayInterface.h
    SMAModbusRelayInterface.cpp
)
target_link_libraries(SMAModbusRelayInterface PUBLIC ObserverModel)
target_link_libraries(SMAModbusRelayInterface PUBLIC ModbusDevice)

add_library(
    SMAModbusRelayDevice
    SMAModbusRelayDevice.h
    SMAModbusRelayDevice.cpp
)
target_link_libraries(SMAModbusRelayDevice PUBLIC SMAModbusRelayInterface)
target_link_libraries(SMAModbusRelayDevice PUBLIC SMADevice)

add_library(
    SMAModbusRelayMains
    SMAModbusRelayMains.h
    SMAModbusRelayMains.cpp
)
target_link_libraries(SMAModbusRelayMains PUBLIC SMAModbusRelayInterface)
target_link_libraries(SMAModbusRelayMains PUBLIC SMADevice)

add_library(
    SMAModbusRelayStorageBoy
    SMAModbusRelayStorageBoy.h
    SMAModbusRelayStorageBoy.cpp
)
target_link_libraries(SMAModbusRelayStorageBoy PUBLIC SMAModbusRelayInterface)
target_link_libraries(SMAModbusRelayStorageBoy PUBLIC SMAStorageBoy)

add_library(SMAModbusRelay INTERFACE)
target_link_libraries(SMAModbusRelay INTERFACE SMAModbusRelayDevice SMAModbusRelayMains SMAModbusRelayStorageBoy)

add_library(SMALIB INTERFACE)
target_link_libraries(SMALIB INTERFACE SMADevice SMASunnyBoy SMAStorageBoy SMAMqtt SMAModbusRelay)

if(PROJECT_IS_TOP_LEVEL)
    find_package(Doxygen
        REQUIRED dot
        OPTIONAL_COMPONENTS mscgen dia
    )
    set(DOXYGEN_EXTRACT_PRIVATE TRUE)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED FALSE)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C TRUE)

    doxygen_add_docs(doxygen_target
        ${CMAKE_SOURCE_DIR}
        COMMENT "Run doxygen_target"
    )
endif()
