#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMADevice.h>

namespace SMA{

    /**
     * @brief Modbus relay for Mains values
     *
     * Used to send the values of mains supply to another modbus device.
     *
     * Values:
     * - Device::mainsFeedIn
     * - Device::mainsSupply
     *
     */
    class ModbusRelayMains : public ModbusRelayInterface
    {
        public:
            /**
             * @brief Construct a new Modbus Relay Mains object
             *
             * @param deviceIn Device the values are read from
             * @param deviceOut Device the values are written to
             * @param addressOffset Register offset of the registers the values are written to
             */
            explicit ModbusRelayMains(std::weak_ptr<Device> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayMains(const ModbusRelayMains& other) = delete;
            virtual ~ModbusRelayMains();
            virtual void update(std::string message = "") override;
            /// Register where the Device::mainsFeedIn value will be written to
            mb::Register<unsigned int>* registerMainsFeedIn = nullptr;
            /// Register where the Device::mainsSupply value will be written to
            mb::Register<unsigned int>* registerMainsSupply = nullptr;
            /**
             * @brief Set the MainsFeedIn register address
             *
             * @param address
             */
            void set_MainsFeedIn_register_address(int address);
            /**
             * @brief Set the MainsSuppy register address
             *
             * @param address
             */
            void set_MainsSuppy_register_address(int address);
            /// Device where the values are read from
            std::weak_ptr<Device> deviceIn;
            /**
             * @brief Relay the mains values
             *
             * Gets called by #update
             *
             * Relays:
             * - Device::mainsFeedIn
             * - Device::mainsSupply
             *
             */
            uint8_t mains_update();

        private:
            /// Previously read Device::mainsFeedIn value
            unsigned int _mainsFeedIn_old;
            /// Previously read Device::mainsSupply value
            unsigned int _mainsSupply_old;
    };
}
