/**
 * @file NetworkInterface.h
 * @brief Объявление класса NetworkInterface.
 */
#pragma once

class IpAddress;

/**
 * @class NetworkInterface
 * @brief Класс сетевого интерфейса (сетевой карты).
 * 
 * Управляет состоянием соединения, привязкой IP-адреса 
 * и передачей данных.
 */
class NetworkInterface{
private:
    bool isUp;///<Флаг активности интерфейса.
    int speedMbps;///<Пропускная способность.
    int bytesSent;///<Счетчик отправленных байт.
    IpAddress* ip;///<Указатель на привязанный IP-адрес.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    NetworkInterface();

/**
 * @brief Конструктор с указанием скорости.
 * @param speedMbps Скорость в Мбит/с.
 */
    explicit NetworkInterface(int speedMbps);

/**
 * @brief Подключает IP-адрес к интерфейсу.
 * @param newIp Указатель на объект IP-адреса.
 * @exception InvalidAddressException если переданный IP некорректен.
 */
    void connect(IpAddress* newIp);

/**
 * @brief Рассчитывает время передачи заданного количества бит.
 * @param bits Количество бит для передачи.
 * @return Время передачи в наносекундах.
 * @exception NetworkDisconnectedException если интерфейс выключен или нет IP.
 */
    int transmitNs(int bits);
};
