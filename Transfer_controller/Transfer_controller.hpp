#ifndef TRANSFER_CONTROLLER_HPP_
#define TRANSFER_CONTROLLER_HPP_

#if defined(linux)
#include <iostream>
#include "../Hal/Hal.hpp"
#elif defined(ESP32)
#include <Arduino.h>
#else // STM32
#include <main.h>
#endif

// --- Про пространства полагаю вы помните, их использование
// --- уменьшает внезапные проблемы, как, например, дублирование
// --- переменных с именем BUFFER_SIZE.
// Data transfer protocol
namespace dtp {

    // Максимальный размер пакета
    const uint8_t BUFFER_SIZE = 50;

    // Состояние обмена информацией
    enum class Stage {
        No_transmission=0,            // Нет передачи
        // Принимающий модуль
        Received_initialization_byte, // Принят инициализирующий байт
        Received_length_byte,         // Принят байт длины
        Receive_bytes,                // Приём байт
        Expect_trailing_byte,         // Ожидается завершающий байт
        // Отправляющий модуль
        Sent_initialization_byte,     // Отправлен инициализирующий байт
        Sent_length_byte,             // Отправлен байт длины
        Sending_bytes,                // Отправка байт
        Sent_trailing_byte,           // Отправлен завершающий байт
        // Количество компонентов
        AMT_COMPONENTS
    };

    // Статус завершения передачи/приёма
    enum class Status {
        Ok=0,      // Передача или приём завершены и обработаны
        Exit,      // Передача или приём завершены и не обработаны
        Error,     // Передача или приём завершены с ошибкой
        // --- Это не сделано, реакция на одновременную отправку 2-х
        // --- модулей друг другу. В этом случае менее приоритетный
        // --- модуль должен будет перейти в состояние Postponed.
        Postponed, // (-) ----- Передача ожидает завершения приёма
        // Количество компонентов
        AMT_COMPONENTS
    };

    // --- Именование с UART не до конца корректно, как я
    // --- рассказывал, может использоваться иной протокол
    // --- обмена. Просто сам сначала с UARTом делал, но
    // --- для ESP и STM с ifdef'ами, но потом просто стал
    // --- с буферами работать, а переименовать, не
    // --- переименовал.
    class Transfer_controller {
        uint8_t send_buffer[BUFFER_SIZE]{};    // буфер отправки
        uint8_t send_len{0};      // отправляемая длина
        uint8_t send_cnt{0};      // отправленная количество
        uint8_t last_send_byte{}; // последний отправленный байт
        Status send_status{Status::Ok};        // статус отправки
        uint8_t receive_buffer[BUFFER_SIZE]{}; // буфер приёма
        uint8_t receive_len{0};   // ожидаемая длина
        uint8_t receive_cnt{0};   // принятое количество

        uint8_t amt_error{0};     // количество произошедших ошибок
        uint8_t max_amt_error{5}; // максимальное количество произошедших ошибок
    public:
        // --- Открываю доступ, т.к. всё равно в uart_receive передаётся
        // --- адрес данного поля, по сути своей можно не открывать,
        // --- или не вставкой, а перенести вниз к конструктору.
        // --- Просто возврат адреса равносилен полному открытию доступа.
        uint8_t last_receive_byte{}; // последний принятый байт
    private:
        Status receive_status{Status::Ok};     // статус приёма
        Stage stage{Stage::No_transmission};   // текущая стадия

        void (*uart_send)(uint8_t &send_byte);
        void (*uart_receive)(uint8_t &receive_byte);
    public:
        Transfer_controller(void (*uart_send)(uint8_t &send_byte), void (*uart_receive)(uint8_t &receive_byte));

        // Сброс всех полей и старт приёма
        void begin();

        // Получение статуса отправки
        Status get_send_status() const;
        // Получение статуса приёма
        Status get_receive_status() const;
        // Получение состояния передачи/приёма
        Stage get_stage() const;

        // Начать отправку буфера данных
        bool send_data(const uint8_t *buffer, uint8_t len);
        // Получить принятые данные
        uint8_t receive_data(uint8_t *buffer, uint8_t len);

        // Завершена отправка байта
        void end_send();
        // Завершён приём байта
        void end_receive();
        // Истекло время ожидания байта
        void receive_timeout();

        // Сбросить состояние отправки
        Status clear_send_status();
        // Сбросить состояние приёма
        Status clear_receive_status();
        // Сбросить состояние всех полей
        void erase();
    };
}

#endif // TRANSFER_CONTROLLER_HPP_
