/**
 * @file Packet.h
 * @brief Объявление класса Packet.
 */
#pragma once
#include <string>

class IpAddress;

/**
 * @class Packet
 * @brief Класс сетевого пакета.
 * 
 * Содержит информацию об отправителе, получателе, размере пакета 
 * и времени жизни (TTL).
 */
class Packet{
private:
    IpAddress* source;///<Указатель на IP-адрес отправителя.
    std::string destination;///<IP-адрес получателя.
    int sizeBytes;///<Размер пакета в байтах.
    int ttl;///<Время жизни пакета.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Packet();

/**
 * @brief Конструктор с параметрами.
 * @param source Указатель на IP отправителя.
 * @param destination IP получателя.
 * @param sizeBytes Размер в байтах.
 * @param ttl Время жизни.
 */
    Packet(IpAddress* source,const std::string& destination,int sizeBytes,int ttl);

/**
 * @brief Продвигает пакет по сети, то есть уменьшает TTL.
 * @return Размер пакета в битах.
 * @exception NetworkDisconnectedException если TTL истек.
 */
    int forward();

/**
 * @brief Проверяет, находится ли получатель в локальной подсети.
 * @return true, если отправитель и получатель в одной подсети.
 */
    bool isLocal();
};
