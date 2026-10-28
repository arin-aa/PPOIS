/**
 * @file MacAddress.h
 * @brief Объявление класса MacAddress.
 */
#pragma once
#include <string>

/**
 * @class MacAddress
 * @brief Класс, представляющий MAC-адрес.
 * 
 * Хранит значение адреса и имя производителя, позволяет проверять 
 * корректность записи MAC-адреса.
 */
class MacAddress{
private:
    std::string value;///<Строковое значение MAC-адреса.
    std::string vendor;///<Название производителя.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    MacAddress();

/**
 * @brief Конструктор с параметрами.
 * @param value Строковое значение MAC-адреса.
 * @param vendor Производитель.
 */
    MacAddress(const std::string& value,const std::string& vendor);

/**
 * @brief Проверяет корректность MAC-адреса.
 * 
 * Проверяет длину строки (должна быть 17 символов) и наличие 
 * разделителей ':' в нужных позициях.
 * @exception InvalidAddressException если формат неверен.
 */
    void verify();
};
