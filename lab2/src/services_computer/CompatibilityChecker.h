/**
 * @file CompatibilityChecker.h
 * @brief Объявление класса CompatibilityChecker.
 */
#pragma once

/**
 * @class CompatibilityChecker
 * @brief Класс для проверки совместимости блока питания и энергопотребления.
 * 
 * Позволяет рассчитать резерв мощности и выбросить исключение, 
 * если резерв ниже минимально допустимого.
 */
class CompatibilityChecker{
private:
    bool strictMode;///<Флаг строгого режима проверки.
    int checksDone;///<Счетчик выполненных проверок.
    int minReserveWatts;///<Минимально допустимый резерв мощности в ваттах.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    CompatibilityChecker();

/**
 * @brief Конструктор с параметрами.
 * @param strictMode Включить ли строгий режим.
 * @param minReserveWatts Минимальный резерв мощности.
 */
    CompatibilityChecker(bool strictMode,int minReserveWatts);

/**
 * @brief Проверяет достаточно ли мощности блока питания.
 * @param supplyWatts Мощность блока питания.
 * @param demandWatts Требуемая мощность.
 * @return Резерв мощности (разница между supplyWatts и demandWatts).
 * @exception InsufficientPowerException если в строгом режиме резерв меньше минимального.
 */
    int checkPower(int supplyWatts,int demandWatts);
};
