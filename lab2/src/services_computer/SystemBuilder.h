/**
 * @file SystemBuilder.h
 * @brief Объявление класса SystemBuilder.
 */
#pragma once

class CompatibilityChecker;

/**
 * @class SystemBuilder
 * @brief Класс-конфигуратор для сборки компьютера.
 * 
 * Отслеживает бюджет, суммарное энергопотребление деталей 
 * и рассчитывает рекомендуемую мощность блока питания.
 */
class SystemBuilder{
private:
    int budget;///<Общий бюджет сборки.
    int spent;///<Потраченная сумма.
    int partsWatts;///<Суммарное энергопотребление деталей.
    CompatibilityChecker* checker;///<Указатель на объект проверки совместимости.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    SystemBuilder();

/**
 * @brief Конструктор с параметрами.
 * @param budget Бюджет.
 * @param checker Указатель на проверяющий модуль.
 */
    SystemBuilder(int budget,CompatibilityChecker* checker);

/**
 * @brief Добавляет деталь в сборку.
 * @param watts Энергопотребление детали.
 * @param price Стоимость детали.
 * @exception InvalidConfigurationException если стоимость превышает бюджет.
 */
    void addPart(int watts,int price);

/**
 * @brief Рассчитывает запас мощности блока питания.
 * @param psuWatts Мощность предполагаемого БП.
 * @return Резерв мощности в ваттах.
 * @exception InsufficientPowerException если резерв недостаточен.
 */
    int powerMargin(int psuWatts);

/**
 * @brief Рекомендует необходимую мощность блока питания.
 * @return Рекомендуемая мощность, округленная вверх до шага 50.
 */
    int recommendedPsu();
};
