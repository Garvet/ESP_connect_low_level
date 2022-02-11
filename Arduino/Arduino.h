//
// Created by garvet on 04.02.2021.
//
#ifndef GCM_MODEL_ARDUINO_H
#define GCM_MODEL_ARDUINO_H

#include <iostream>
#include <cstdint>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <cstring>

#define PIPE_MODE (S_IRWXO | S_IRWXG | S_IRWXU)

//int LoRa_create_file(const char* pipe_name);
//uint16_t LoRa_send(const char* pipe_name, uint8_t* buf, uint16_t size, bool wait=false);
//int LoRa_receive(const char* pipe_name, uint8_t* buf, uint16_t max_size);

void delay(ulong ms);
ulong millis();

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
class HardwareSerial {
public:
    static size_t write(uint8_t);
    static size_t write(const uint8_t *buffer, size_t size);
    static inline size_t write(const char * buffer, size_t size);
    static inline size_t write(const char * s);
    static inline size_t write(unsigned long n);
    static inline size_t write(long n);
    static inline size_t write(unsigned int n);
    static inline size_t write(int n);
    //
    static size_t printNumber(unsigned long long n, uint8_t base);
    size_t printFloat(double number, uint8_t digits);
    // print + println
    size_t print(const char*);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(long long, int = DEC);
    size_t print(unsigned long long, int = DEC);
    size_t print(double, int = 2);
    size_t print(struct tm * timeinfo, const char * format = nullptr);

    size_t println(const char*);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(long long, int = DEC);
    size_t println(unsigned long long, int = DEC);
    size_t println(double, int = 2);
    size_t println(struct tm * timeinfo, const char * format = nullptr);
    size_t println();
};

extern HardwareSerial Serial;

#endif // GCM_MODEL_ARDUINO_H
