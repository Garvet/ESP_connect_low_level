//
// Created by Garvet on 10.02.2022.
//

#include "System_component.hpp"

// <<< system components control >>>
namespace scc {
    // <<< system id >>>
    namespace sid {
        Id::Id(std::array<uint8_t, AMT_BYTES_ID> new_id) {
            system_id = new_id;
        }

        void Id::set_id(const std::array<uint8_t, AMT_BYTES_ID> *new_id) {
            system_id = *new_id;
        }

        void Id::set_id(const uint8_t *new_id) {
            for(int i = 0; i < AMT_BYTES_ID; ++i)
                system_id[i] = new_id[i];
        }

        std::array<uint8_t, AMT_BYTES_ID> Id::get_id() {
            return system_id;
        }

        const std::array<uint8_t, AMT_BYTES_ID>& Id::get_id() const {
            return system_id;
        }

        void Id::get_id(uint8_t *id) const {
            for(int i = 0; i < AMT_BYTES_ID; ++i)
                id[i] = system_id[i];
        }

        std::array<char, AMT_STR_ID> Id::get_str_id() const {
            std::array<char, AMT_STR_ID> str{};
            convert_to_hex(&system_id[0], &str[0], AMT_BYTES_ID);
            return str;
        }

        void Id::get_str_id(char *id) const {
            convert_to_hex(&system_id[0], id, AMT_BYTES_ID);
        }

        void Id::print_id() const {
            std::array<char, AMT_STR_ID> str{};
            convert_to_hex(&system_id[0], &str[0], AMT_BYTES_ID);
            Serial.print('{');
            for(int i = 0; i < AMT_BYTES_ID; ++i) {
                Serial.print(str[i * 2]);
                Serial.print(str[i * 2 + 1]);
                if(i < AMT_STR_ID - 1)
                    Serial.print(", ");
            }
            Serial.print('}');
        }
    }

    // ----- class System_component -----
    void System_component::set_basic_LoRa_settings(lrc::lrs::LoRa_setting setting) {
        lora_basic = setting;
    }

    lrc::lrs::LoRa_setting System_component::get_basic_LoRa_settings() {
        return lora_basic;
    }

    const lrc::lrs::LoRa_setting& System_component::get_basic_LoRa_settings() const {
        return lora_basic;
    }

    // ----- class Router -----
    bool Router::set_additional_LoRa_settings(lrc::lrs::LoRa_setting setting, uint8_t num) {
        if(AMT_LORA < num)
            return true;
        lora_additional[num] = setting;
        return false;
    }

    lrc::lrs::LoRa_setting Router::get_additional_LoRa_settings(uint8_t num) {
        return lora_additional[num];
    }

    const lrc::lrs::LoRa_setting &Router::get_additional_LoRa_settings(uint8_t num) const {
        return lora_additional[num];
    }

    void Router::set_additional_LoRa_settings(std::array<lrc::lrs::LoRa_setting, AMT_LORA> setting) {
        lora_additional = setting;
    }

    std::array<lrc::lrs::LoRa_setting, AMT_LORA> Router::get_additional_LoRa_settings() {
        return lora_additional;
    }

    const std::array<lrc::lrs::LoRa_setting, AMT_LORA> &Router::get_additional_LoRa_settings() const {
        return lora_additional;
    }

}
