/**
 * @file CPU.h
 * @brief Объявление класса CPU.
 */
#pragma once
#include <string>
#include "Component.h"

class Sensor;

/**
 * @class CPU
 * @brief Класс процессора.
 */
class CPU:public Component{
private:
    int cores;///<Количество ядер.
    double frequencyGhz;///<Тактовая частота в ГГц.
    int loadPercent;///<Текущая загрузка в процентах.
    std::string socket;///<Сокет процессора.
    Sensor* tempSensor;///<Указатель на датчик температуры.

public:
/**
* @brief Конструктор по умолчанию.
*/
    CPU();

/**
 * @brief Конструктор с параметрами.
 * @param socket Сокет.
 * @param cores Количество ядер.
 * @param frequencyGhz Частота.
 * @param tempSensor Датчик температуры (по умолчанию nullptr).
 */
    CPU(const std::string& socket,int cores,double frequencyGhz,Sensor* tempSensor=nullptr);

/**
 * @brief Запускает нагрузку на процессор.
 * @param percent Процент нагрузки.
 * @exception InvalidConfigurationException если нагрузка вне диапазона от 0 до 100.
 * @exception OverheatingException при критической температуре.
 */
    void runLoad(int percent);

/**
 * @brief Проверяет совместимость сокета процессора с материнской платой.
 * @param boardSocket Сокет платы.
 * @exception IncompatibleSocketException при несовпадении.
 */
    void checkSocket(const std::string& boardSocket);
};
