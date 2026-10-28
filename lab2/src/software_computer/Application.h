/**
 * @file Application.h
 * @brief Объявление класса Application.
 */
#pragma once
#include "Software.h"

/**
 * @class Application
 * @brief Класс пользовательского приложения, наследуемый от Software.
 */
class Application:public Software{
private:
    int requiredRamMb;///<Требуемый объем оперативной памяти.
    std::string licenseKey;//<Лицензионный ключ приложения.
    int launches;///<Счетчик успешных запусков.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Application();

/**
 * @brief Конструктор с параметрами.
 * @param name Название приложения.
 * @param sizeMb Размер в МБ.
 * @param requiredRamMb Требуемая оперативная память.
 * @param licenseKey Лицензионный ключ.
 */
    Application(const std::string& name,int sizeMb,int requiredRamMb,const std::string& licenseKey);

/**
 * @brief Проверяет правильность лицензионного ключа.
 * @param key Проверяемый ключ.
 * @return true, если ключ совпадает и не пуст.
 */
    bool checkLicense(const std::string& key);

/**
 * @brief Запускает приложение.
 * @param freeRamMb Доступная свободная оперативная память.
 * @return Оставшаяся свободная память после запуска.
 * @exception InvalidConfigurationException если приложение не установлено.
 * @exception MemoryOverflowException если недостаточно оперативной памяти.
 */
    int launch(int freeRamMb);
};
