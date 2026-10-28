/**
 * @file Battery.h
 * @brief Объявление класса Battery.
 */
#pragma once

/**
 * @class Battery
 * @brief Класс, описывающий аккумуляторную батарею.
 */
class Battery{
private:
    int capacityWh;///<Полная емкость батареи в ватт-часах.
    int chargePercent;///<Текущий уровень заряда в процентах.
    int cycles;///<Количество полных циклов зарядки.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Battery();

/**
 * @brief Конструктор с параметрами.
 * @param capacityWh Емкость.
 * @param chargePercent Начальный заряд.
 */
    Battery(int capacityWh,int chargePercent);

/**
 * @brief Заряжает батарею.
 * @param percent Количество процентов для зарядки.
 * @return Итоговый уровень заряда.
 */
    int charge(int percent);

/**
 * @brief Рассчитывает время автономной работы при заданном потреблении.
 * @param watts Потребляемая мощность устройства.
 * @return Время работы в минутах.
 */
    int runtimeMinutes(int watts);
};
