/**
 * @file IpAddress.h
 * @brief Объявление класса IpAddress.
 */
#pragma once
#include <string>

/**
 * @class IpAddress
 * @brief Класс, представляющий IP-адрес.
 * 
 * Хранит строковое представление адреса и маску подсети, 
 * позволяет проверять корректность адреса и сравнивать подсети.
 */
class IpAddress{
private:
    std::string address;///<Строковое представление IP-адреса.
    int subnetMask;///<Маска подсети.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    IpAddress();

/**
 * @brief Конструктор с параметрами.
 * @param address Строковое представление IP.
 * @param subnetMask Маска подсети.
 */
    IpAddress(const std::string& address,int subnetMask);

/**
 * @brief Проверяет корректность IP-адреса.
 * 
 * Разбирает строку, проверяя наличие 4 октетов и их значения.
 * @exception InvalidAddressException если адрес имеет неверный формат.
 */ 
    void validate();

/**
 * @brief Проверяет, находится ли другой IP в той же подсети.
 * @param other Строковое представление другого IP.
 * @return true, если адреса в одной подсети.
 * @exception InvalidAddressException если текущий или переданный адрес некорректен.
 */
    bool sameSubnet(const std::string& other);
};
