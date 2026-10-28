/**
 * @file Case.h
 * @brief Объявление класса Case.
 */
#pragma once
#include <vector>
#include "Component.h"

class Fan;

/**
 * @class Case
 * @brief Класс корпуса компьютера, наследуемый от Component.
 */
class Case:public Component{
private:
    int maxFans;///<Максимальное количество вентиляторов.
    int dustLevel;///<Уровень запыленности.
    std::vector<Fan*> fans;///<Установленные вентиляторы.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Case();

/**
 * @brief Конструктор с указанием максимального количества вентиляторов.
 * @param maxFans Максимум вентиляторов.
 */ 
    explicit Case(int maxFans);

/**
 * @brief Устанавливает вентилятор в корпус.
 * @param fan Указатель на вентилятор.
 * @exception InvalidConfigurationException если все места заняты.
 */
    void addFan(Fan* fan);

/**
 * @brief Рассчитывает общий воздушный поток с учетом запыленности.
 * @return Суммарный поток.
 */
    int totalAirflow();
};
