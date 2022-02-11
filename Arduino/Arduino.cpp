//
// Created by garvet on 05.02.2021.
//
#include <cmath>
#include "Arduino.h"

HardwareSerial Serial;

//int LoRa_create_file(const char* pipe_name) {
//    return mkfifo(pipe_name, PIPE_MODE);
//}
//
//uint16_t LoRa_send(const char* pipe_name, uint8_t* buf, uint16_t size, bool wait) {
//    int fd, oflag;
//    uint16_t size_send;
//    if(wait)
//        oflag = O_CREAT | O_WRONLY;
//    else
//        oflag = O_CREAT | O_RDWR;
//    fd = open(pipe_name, oflag);
//    write(fd, &size, sizeof(size));
//    size_send = write(fd, buf, size);
//    close(fd);
//    return size_send;
//}
//
//int LoRa_receive(const char* pipe_name, uint8_t* buf, uint16_t max_size) {
//    int fd;
//    uint16_t size_receive;
//    uint16_t read_bytes;
//    fd = open(pipe_name, O_RDONLY);
//    read_bytes = read(fd, &size_receive, sizeof(size_receive));
//    if((read_bytes == sizeof(size_receive)) && (size_receive <= max_size)) {
//        size_receive = read(fd, buf, size_receive);
//    }
//    else
//        return (-size_receive);
//    return size_receive;
//}

void delay(ulong ms) {
    sleep(ms/1000);
}

ulong millis() {
    time_t get_time;
    time(&get_time);
    return ulong(get_time*1000);
}

size_t HardwareSerial::write(uint8_t byte) {
    std::cout << byte;
    return 1;
}
size_t HardwareSerial::write(const uint8_t *buffer, size_t size) {
    for(int i = 0; i < size; ++i)
        std::cout << buffer[i];
    return size;
}
inline size_t HardwareSerial::write(const char * buffer, size_t size) {
    return write((uint8_t*) buffer, size);
}
inline size_t HardwareSerial::write(const char * s) {
    return write((uint8_t*) s, strlen(s));
}
inline size_t HardwareSerial::write(unsigned long n) {
    return write((uint8_t) n);
}
inline size_t HardwareSerial::write(long n) {
    return write((uint8_t) n);
}
inline size_t HardwareSerial::write(unsigned int n) {
    return write((uint8_t) n);
}
inline size_t HardwareSerial::write(int n) {
    return write((uint8_t) n);
}
//

size_t HardwareSerial::printNumber(unsigned long long n, uint8_t base) {
    char buf[8 * sizeof(n) + 1]; // Assumes 8-bit chars plus zero byte.
    char* str = &buf[sizeof(buf) - 1];
    *str = '\0';
    // prevent crash if called with base == 1
    if (base < 2) {
        base = 10;
    }
    do {
        auto m = n;
        n /= base;
        char c = m - base * n;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while (n);
    return write(str);
}

size_t HardwareSerial::printFloat(double number, uint8_t digits) {
    size_t n = 0;
//    if(isnan(number)) {
//        return print("nan");
//    }
//    if(isinf(number)) {
//        return print("inf");
//    }
    if(number > 4294967040.0) {
        return print("ovf");    // constant determined empirically
    }
    if(number < -4294967040.0) {
        return print("ovf");    // constant determined empirically
    }

    // Handle negative numbers
    if(number < 0.0) {
        n += print('-');
        number = -number;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for(uint8_t i = 0; i < digits; ++i) {
        rounding /= 10.0;
    }

    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part = (unsigned long) number;
    double remainder = number - (double) int_part;
    n += print(int_part);

    // Print the decimal point, but only if there are digits beyond
    if(digits > 0) {
        n += print(".");
    }

    // Extract digits from the remainder one at a time
    while(digits-- > 0) {
        remainder *= 10.0;
        int toPrint = int(remainder);
        n += print(toPrint);
        remainder -= toPrint;
    }

    return n;
}
//
size_t HardwareSerial::print(const char *str) {
    for(int i = 0; i < strlen(str); ++i)
        std::cout << str[i];
    return strlen(str);
}

size_t HardwareSerial::print(char c) {
    std::cout << c;
    return 1;
}

size_t HardwareSerial::print(unsigned char b, int base) {
    return print((unsigned long) b, base);
}

size_t HardwareSerial::print(int n, int base)
{
    return print((long) n, base);
}

size_t HardwareSerial::print(unsigned int n, int base)
{
    return print((unsigned long) n, base);
}

size_t HardwareSerial::print(long n, int base) {
    int t = 0;
    if (base == 10 && n < 0) {
        t = print('-');
        n = -n;
    }
    return printNumber(static_cast<unsigned long>(n), base) + t;
}

size_t HardwareSerial::print(unsigned long n, int base)
{
    if(base == 0) {
        return write(n);
    } else {
        return printNumber(n, base);
    }
}

size_t HardwareSerial::print(long long n, int base)
{
    int t = 0;
    if (base == 10 && n < 0) {
        t = print('-');
        n = -n;
    }
    return printNumber(static_cast<unsigned long long>(n), base) + t;
}

size_t HardwareSerial::print(unsigned long long n, int base)
{
    if (base == 0) {
        return write(0);
    } else {
        return printNumber(n, base);
    }
}

size_t HardwareSerial::print(double n, int digits)
{
    return printFloat(n, digits);
}

size_t HardwareSerial::print(struct tm * timeinfo, const char * format)
{
    const char * f = format;
    if(!f){
        f = "%c";
    }
    char buf[64];
    size_t written = strftime(buf, 64, f, timeinfo);
    if(written == 0){
        return written;
    }
    return print(buf);
}

size_t HardwareSerial::println()
{
    return print("\r\n");
}

size_t HardwareSerial::println(const char* c)
{
    size_t n = print(c);
    n += println();
    return n;
}

size_t HardwareSerial::println(char c)
{
    size_t n = print(c);
    n += println();
    return n;
}

size_t HardwareSerial::println(unsigned char b, int base)
{
    size_t n = print(b, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(int num, int base)
{
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(unsigned int num, int base)
{
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(long num, int base)
{
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(unsigned long num, int base)
{
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(long long num, int base)
{
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(unsigned long long num, int base)
{
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t HardwareSerial::println(double num, int digits)
{
    size_t n = print(num, digits);
    n += println();
    return n;
}

size_t HardwareSerial::println(struct tm * time_info, const char * format)
{
    size_t n = print(time_info, format);
    n += println();
    return n;
}

