#include <SMAStorageBoyMqtt.h>
#include <cmath>
#include <cassert>


namespace SMA {
    StorageBoyMqtt::StorageBoyMqtt(std::string name_, std::shared_ptr<StorageBoy> storageBoy_, std::shared_ptr<myMqtt::Client> client_):
        storageBoy(storageBoy_),
        MqttInterface(name_, client_)
    {

    }

    void StorageBoyMqtt::device_update()
    {
        if(abs(static_cast<int>(storageBoy->power())-static_cast<int>(_power_old))>3 || first_run){
            client->publish(base_topic+"power",std::to_string(storageBoy->power()),1,true);
            _power_old = storageBoy->power();
        }

        if(abs(static_cast<int>(storageBoy->dcWatt())-static_cast<int>(_dcWatt_old))>3 || first_run){
            client->publish(base_topic+"dcWatt",std::to_string(storageBoy->dcWatt()),1,true);
            _dcWatt_old = storageBoy->dcWatt();
        }
    }

    void StorageBoyMqtt::storageboy_update()
    {
        if(abs(static_cast<int>(storageBoy->_soc)-static_cast<int>(_soc_old))>3 || first_run){
            client->publish(base_topic+"soc",std::to_string(storageBoy->_soc),1,true);
            _soc_old = storageBoy->_soc;
        }

        if(abs(static_cast<int>(storageBoy->_dischargeCurrent)-static_cast<int>(_dischargeCurrent_old))>3 || first_run){
            client->publish(base_topic+"dischargeCurrent",std::to_string(storageBoy->_dischargeCurrent),1,true);
            _dischargeCurrent_old = storageBoy->_dischargeCurrent;
        }

        if(abs(static_cast<int>(storageBoy->_chargeCurrent)-static_cast<int>(_chargeCurrent_old))>3 || first_run){
            client->publish(base_topic+"chargeCurrent",std::to_string(storageBoy->_chargeCurrent),1,true);
            _chargeCurrent_old = storageBoy->_chargeCurrent;
        }

        if(first_run){
            client->publish(base_topic+"maxDischargeCurrent",std::to_string(storageBoy->_maxDischargeCurrent),1,true);
        }

        if(first_run){
            client->publish(base_topic+"maxChargeCurrent",std::to_string(storageBoy->_maxChargeCurrent),1,true);
        }
        return;
    }

    void StorageBoyMqtt::update(std::string message)
    {
        if(_send_mqtt)
        {
            update_base_topic();
            device_update();
            storageboy_update();
            if(first_run)
                first_run = false;
        }
    }
}
