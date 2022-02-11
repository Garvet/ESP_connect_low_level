//
// Created by Garvet on 10.02.2022.
//

#ifndef SYSTEM_COMPONENT_HPP_
#define SYSTEM_COMPONENT_HPP_

#if defined( linux )
#include "../Arduino/Arduino.h"
#include "../Additional_functionality/Additional_functionality.hpp"
#include "../LoRa/LoRa_setting.hpp"
#else // use linux
#if defined ( ESP32 )
#include <Arduino.h>
#endif
#include <Packet_analyzer.h> // [packet_analyzer]
#include <Additional_functionality.hpp>
#include <LoRa_setting.hpp>
#endif // use linux

#include <array>

// <<< system components control >>>
namespace scc {
    // <<< system id >>>
    namespace sid {
        const uint8_t AMT_BYTES_ID = 12;
        const uint8_t AMT_STR_ID = AMT_BYTES_ID * 2;

        class Id {
            std::array<uint8_t, AMT_BYTES_ID> system_id{};
        public:
            Id()=default;
            Id(std::array<uint8_t, AMT_BYTES_ID>);
            // Установить ID
            void set_id(const std::array<uint8_t, AMT_BYTES_ID>* new_id);
            void set_id(const uint8_t* new_id);
            // Вернуть ID
            std::array<uint8_t, AMT_BYTES_ID> get_id();
            const std::array<uint8_t, AMT_BYTES_ID>& get_id() const;
            void get_id(uint8_t* id) const; // size = AMT_BYTES_ID
            std::array<char, AMT_STR_ID> get_str_id() const;
            void get_str_id(char* id) const; // size = AMT_STR_ID
            // Вывести ID в Serial
            void print_id() const;
        };
    }
    // <<< () >>>

    // <<< () >>>
    // <<< () >>>
    class System_component /*: public SAVE_CLASS (он : public BYTE_CLASS)*/ {
    protected:
        lrc::lrs::LoRa_setting lora_basic;
    public:
        virtual ~System_component() = default;

        void set_basic_LoRa_settings(lrc::lrs::LoRa_setting);
        lrc::lrs::LoRa_setting get_basic_LoRa_settings();


    };


    class Router : public System_component {
    protected:
        lrc::lrs::LoRa_setting lora_additional[3];
    public:
        ~Router() override = default;
    };
}

#endif // SYSTEM_COMPONENT_HPP_
