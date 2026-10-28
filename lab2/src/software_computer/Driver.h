/**
 * @file Driver.h
 * @brief Объявление класса Driver.
 */
#pragma once
#include "Software.h"

class Component;

/**
 * @class Driver
 * @brief Класс драйвера устройства, наследуемый от Software.
 */
class Driver:public Software{
private:
    std::string deviceName;///<Имя устройства, для которого предназначен драйвер.
    bool isSigned;///<Флаг наличия цифровой подписи.
    int bindCount;///<Счетчик успешных привязок к устройствам.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Driver();

/**
 * @brief Конструктор с параметрами.
 * @param name Название драйвера.
 * @param deviceName Имя устройства.
 * @param isSigned Наличие подписи.
 */
    Driver(const std::string& name,const std::string& deviceName,bool isSigned);

/**
 * @brief Привязывает драйвер к компоненту.
 * @param part Указатель на компонент.
 * @exception DriverNotFoundException если драйвер не подходит к этому устройству.
 */
    void bind(Component* part);

/**
 * @brief Загружает драйвер в систему.
 * @exception BootFailureException если драйвер не имеет цифровой подписи.
 */
    void load();
};
