/**
 * @file Server.h
 * @brief Объявление класса Server.
 */
#pragma once
#include <vector>
#include "Computer.h"

class NetworkInterface;
class Packet;

/**
 * @class Server
 * @brief Производный класс, представляющий сервер.
 * 
 * Расширяет базовый класс Computer, добавляя поддержку RAID, 
 * обработку сетевых запросов и учет юнитов.
 */
class Server:public Computer{
private:
    int rackUnits;///<Количество юнитов.
    std::string raidLevel;///<Текущий уровень RAID
    int requestsServed;///<Счетчик успешно обработанных запросов.
    std::vector<NetworkInterface*> nics;///<Вектор сетевых интерфейсов (карт).

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Server();

/**
 * @brief Конструктор с параметрами.
 * @param hostname Сетевое имя сервера.
 * @param rackUnits Количество занимаемых юнитов.
 * @param firstNic Указатель на первую сетевую карту.
 */
    Server(const std::string& hostname,int rackUnits,NetworkInterface* firstNic);

/**
 * @brief Настраивает уровень RAID.
 * @param level Строка с уровнем RAID.
 * @return Процент полезной емкости дисков для данного уровня RAID.
 * @exception InvalidConfigurationException если передан неизвестный уровень RAID.
 */
    int configureRaid(const std::string& level);

/**
 * @brief Обрабатывает входящий сетевой пакет.
 * @param packet Указатель на пакет.
 * @return Время обработки пакета в наносекундах.
 * @exception NetworkDisconnectedException если у сервера нет сетевых карт.
 */
    int handleRequest(Packet* packet);

/**
 * @brief Переопределенный метод расчета энергопотребления.
 * Учитывает потребление сетевых карт и занимаемых юнитов стойки.
 * @return Потребляемая мощность в ваттах.
 */   
    int powerDraw() override;
};
