#pragma once
#include <ModbusDevice.h>
#include <ModbusRegister.h>

namespace SMA
{
    /**
     * @brief Interface to a SMA device such as SMA SolarBoy
     *
     */
    class Device : public mb::Device
    {
        // function
    public:
        /**
         * @brief Construct a new Device object
         *
         * @param ipAddress Ip address of the device
         * @param port Port number of the device
         */
        explicit Device(std::string ipAddress, int port = 502);
        Device(const Device &other) = delete;
        ~Device() = default;
        /**
         * @brief Reboot the device
         *
         */
        void reboot();
        /**
         * @brief Test whether the device is online
         *
         */
        void test();

        /**
         * @brief Read power register
         *
         * @param ret Return status (true: success, false: fail)
         * @return unsigned int: Power value
         */
        unsigned int power(bool force = false, bool *ret = nullptr) const;
        /**
         * @brief Read dcWatt register
         *
         * @param ret Return status (true: success, false: fail)
         * @return unsigned int: DcWatt value
         */
        unsigned int dcWatt(bool force = false, bool *ret = nullptr) const;
        /**
         * @brief Get the feedIn to mains register
         *
         * Mains <- Local Grid
         *
         * @param ret Return status (true: success, false: fail)
         * @return unsigned int: FeedIn to mains
         */
        unsigned int mainsFeedIn(bool force = false, bool *ret = nullptr) const;
        /**
         * @brief Get the supply from mains register
         *
         * Mains -> Local Grid
         *
         * @param ret Return status (true: success, false: fail)
         * @return unsigned int: Supply from mains
         */
        unsigned int mainsSupply(bool force = false, bool *ret = nullptr) const;

        /**
         * @brief Test read the device
         *
         * @param ret Return status (true: success, false: fail)
         */
        void testRead(bool *ret = nullptr);

    private:
        /**
         * @brief Initialize the device
         *
         * Read constant device variables, such as slaveId_, physicalSusyId_, physicalSerialNumber_, model_
         *
         */
        void deviceInit();
        /**
         * @brief Parse device information from uint16_t[4] array
         *
         */
        void parseDeviceInfo();

        // properties
    public:
        /**
         * @brief Serial number of the device
         *
         */
        unsigned int serialNumber_{0};

    private:
        /**
         * @brief Modbus slave id of the device
         *
         */
        short slaveId_{3};
        /**
         * @brief physical Susy Id of the device
         *
         */
        unsigned short physicalSusyId_{0};
        /**
         * @brief Physical serial number of the device
         *
         */
        unsigned int physicalSerialNumber_{0};
        /**
         * @brief Model code of the device
         *
         */
        unsigned int model_{0};
        /**
         * @brief Register of the device info
         *
         */
        mb::Register<long long> mbReg_deviceInfo;
        /**
         * @brief Register of the serial number
         *
         */
        mb::Register<unsigned int> mbReg_serialNumber;
        /**
         * @brief Register of the model code
         *
         */
        mb::Register<unsigned int> mbReg_model;
        /**
         * @brief Register to reboot the device
         *
         */
        mb::Register<unsigned int> mbReg_rebootRegister;
        /**
         * @brief Register of the power value
         *
         */
        mb::Register<unsigned int> mbReg_power;
        /**
         * @brief Register of the dcWatt value
         *
         */
        mb::Register<unsigned int> mbReg_dcWatt;
        /**
         * @brief Register of the mains FeedIn value
         *
         */
        mb::Register<unsigned int> mbReg_mainsFeedIn;
        /**
         * @brief Register of the mains supply value
         *
         */
        mb::Register<unsigned int> mbReg_mainsSupply;
    };
}
