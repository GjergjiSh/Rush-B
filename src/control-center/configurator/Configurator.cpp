#include "Configurator.h"

Configurator::Configurator(const char* config_path)
{
    this->config_path = config_path;
    Load_Config();
    Parse_Config();
    Print_Config();
}

int32_t Configurator::Load_Config()
{
    try {
        this->config.load_file(this->config_path);
    } catch (const std::exception& ex) {
        CLOG_ERROR("Failed to load config file", ex.what());
        return -1;
    }
    return 0;
}

void Configurator::Parse_Config()
{
    pugi::xml_node root = this->config.child("Config");
    pugi::xml_node ci = root.first_child();
    int i = 0;

    for (pugi::xml_node child = ci.first_child(); child; child = child.next_sibling()) {

        for (pugi::xml_attribute attr = child.first_attribute(); attr; attr = attr.next_attribute()) {
            this->config_items.emplace(std::make_pair(i, attr.value()));
            i++;
        }
    }
}

void Configurator::Print_Config()
{
    std::cout << "[I] Active Device: " << config_items.at(DEVICE) << std::endl;
    std::cout << "[I] Active Device Path: " << config_items.at(DEVICE_PATH) << std::endl;
    std::cout << "[I] ZMQ Pipeline - TCP Transport: " << config_items.at(TCP_TRANSPORT) << std::endl;
    std::cout << "[I] ZMQ Pipeline - Interface ACTIVE: " << config_items.at(PY_INTERFACE_ACTIVE) << std::endl;
    std::cout << "[I] ZMQ Pipeline - Interface Transport: " << config_items.at(INTERFACE_TRANSPORT) << std::endl;
    std::cout << "[I] Video Pipeline - Video Port: " << config_items.at(VIDEO_PORT) << std::endl;
}
