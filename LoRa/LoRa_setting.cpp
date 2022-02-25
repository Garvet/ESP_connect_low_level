//
// Created by garvet on 11.02.2022.
//

#include "LoRa_setting.hpp"

// <<< LoRa controller >>>
namespace lrc {
    // <<< LoRa setting >>>
    namespace lrs {
        LoRa_setting::LoRa_setting(uint32_t new_freq, Spreading_factor new_sf, Bandwidth new_bw, Coding_rate new_cr) {
            freq = new_freq;
            sf = new_sf;
            bw = new_bw;
            cr = new_cr;
        }
        // Установить настройки
        void LoRa_setting::set_freq(uint32_t new_freq) {
            freq = new_freq;
        }
        void LoRa_setting::set_sf(Spreading_factor new_sf) {
            sf = new_sf;
        }
        void LoRa_setting::set_bw(Bandwidth new_bw) {
            bw = new_bw;
        }
        void LoRa_setting::set_cr(Coding_rate new_cr) {
            cr = new_cr;
        }
        // Получить настройки
        uint32_t LoRa_setting::get_freq() const {
            return freq;
        }
        Spreading_factor LoRa_setting::get_sf() const {
            return sf;
        }
        Bandwidth LoRa_setting::get_bw() const {
            return bw;
        }
        Coding_rate LoRa_setting::get_cr() const {
            return cr;
        }

    }
}