/**
 * @file Component.h
 * @brief Объявление базового класса Component.
 */
#pragma once
#include <string>

/**
 * @class Component
 * @brief Базовый класс для всех комплектующих компьютера.
 * 
 * Содержит общие свойства (название, производитель, потребляемая мощность) 
 * и методы для идентификации и расчета нагрузки.
 */
class Component{
protected:
    std::string name;///<Название компонента.
    std::string manufacturer;///<Производитель.
    int powerWatts;///<Потребляемая мощность

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Component();

/**
 * @brief Конструктор с параметрами.
 * @param name Название компонента.
 * @param manufacturer Производитель.
 * @param powerWatts Потребляемая мощность (в ваттах).
 */
    Component(const std::string& name,const std::string& manufacturer,int powerWatts);

/**
 * @brief Виртуальный деструктор по умолчанию.
 */
    virtual ~Component()=default;

/**
 * @brief Проверяет, совпадает ли переданная строка с именем или производителем.
 * @param key Искомая строка.
 * @return true, если совпадение найдено.
 */
    bool isNamed(const std::string& key);

/**
 * @brief Рассчитывает текущее энергопотребление с учетом нагрузки.
 * @param loadPercent Процент нагрузки.
 * @return Потребляемая мощность.
 */
    int draw(int loadPercent);
};
