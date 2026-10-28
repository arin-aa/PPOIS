/**
 * @file Technician.h
 * @brief Объявление класса Technician.
 */
#pragma once
#include "User.h"

class Inventory;
class Component;

/**
 * @class Technician
 * @brief Класс техника, наследуемый от User.
 * 
 * Представляет сотрудника сервисного центра, который может выполнять ремонт 
 * и заказывать детали со склада.
 */
class Technician:public User{
private:
    std::string specialization;///<Специализация техника.
    int experienceYears;///<Стаж работы в годах.
    int repairsDone;///<Количество выполненных ремонтов.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Technician();

/**
 * @brief Конструктор с параметрами.
 * @param login Логин.
 * @param password Пароль.
 * @param specialization Специализация.
 * @param experienceYears Стаж.
 */
    Technician(const std::string& login,const std::string& password,const std::string& specialization,int experienceYears);

/**
 * @brief Рассчитывает стоимость работы техника.
 * @param hours Количество затраченных часов.
 * @return Итоговая стоимость.
 */
    int estimate(int hours);

/**
 * @brief Заказывает деталь со склада.
 * @param stock Указатель на склад.
 * @param key Искомый ключ (имя или производитель).
 * @return Указатель на полученную деталь.
 * @exception InvalidConfigurationException если детали нет на складе.
 */
    Component* orderPart(Inventory* stock,const std::string& key);
};
