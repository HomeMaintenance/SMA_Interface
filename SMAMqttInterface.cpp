#include <SMAMqttInterface.h>


namespace SMA{
    MqttInterface::MqttInterface(std::string name_,  std::shared_ptr<myMqtt::Client> client_):
        Observer(name_),
        name(name_),
        client(client_)
    {
    }

    void MqttInterface::sending(bool send_status)
    {
        _send_mqtt = send_status;
    }

    void MqttInterface::update(std::string message)
    {
        return;
    }

    void MqttInterface::update_base_topic()
    {
        std::string base_topic_ = "";
        if(!topicPrefix.empty()){
            base_topic_ += topicPrefix+"/";
        }
        base_topic = base_topic_ + name+"/";
    }
}
