//
// Created by garvet on 11.02.2022.
//

#ifndef LORA_SETTING_HPP_
#define LORA_SETTING_HPP_

#if defined( linux )
#include "../Arduino/Arduino.h"
#elif defined ( ESP32 )
#include <Arduino.h>
#else // STM32
#include <main.h>
#endif // use linux

// <<< LoRa controller >>>
namespace lrc {
    // <<< LoRa setting >>>
    namespace lrs {
        enum class Spreading_factor: uint8_t {
            CS64 = 6, // 64 Ч/С
            CS128,    // 128 Ч/С
            CS256,    // 256 Ч/С
            CS512,    // 512 Ч/С
            CS1024,   // 1024 Ч/С
            CS2048,   // 2048 Ч/С
            CS4096,   // 4096 Ч/С
        };
        enum class Bandwidth: uint8_t {
            BW7KH8 = 0, // 7,8 КГц
            BW10KH4,    // 10,4 КГц
            BW15KH6,    // 15,6 КГц
            BW20KH8,    // 20,8 КГц
            BW31KH2,    // 31,2 КГц
            BW41KH7,    // 41,7 КГц
            BW92KH5,    // 92,5 КГц
            BW125KH0,   // 125 КГц
            BW250KH0,   // 250 КГц
            BW500KH0,   // 500 КГц
        };
        enum class Coding_rate: uint8_t {
            CR4to5 = 0, // 4/5
            CR4to6,     // 4/6
            CR4to7,     // 4/7
            CR4to8,     // 4/8
        };

        class LoRa_setting {
            uint32_t freq{};       // Частота работы
            Spreading_factor sf{}; // Фактор распространения
            Bandwidth bw{};        // Пропускная способность
            Coding_rate cr{};      // Коэффициент кодирования
        public:
            LoRa_setting() = default;
            LoRa_setting(uint32_t, Spreading_factor, Bandwidth, Coding_rate);
            // Установить настройки
            void setFreq(uint32_t new_freq);
            void setSf(Spreading_factor new_sf);
            void setBw(Bandwidth new_bw);
            void setCr(Coding_rate new_cr);
            // Получить настройки
            uint32_t getFreq() const;
            Spreading_factor getSf() const;
            Bandwidth getBw() const;
            Coding_rate getCr() const;
        };
    }
}


#endif // LORA_SETTING_HPP_
