/**
 * @file Computer.h
 * @brief Объявление базового класса Computer.
 */
#pragma once
#include <string>
#include <vector>

class Motherboard;
class PSU;
class Storage;
class OperatingSystem;

/**
 * @class Computer
 * @brief Класс, представляющий персональный компьютер.
 * 
 * Хранит информацию о комплектующих (материнская плата, блок питания, накопители),
 * позволяет собирать систему, устанавливать ОС и рассчитывать энергопотребление.
 * Является базовым классом для Laptop, Server и Workstation.
 */
class Computer{
protected:
    std::string hostname;///<Сетевое имя компьютера.
    int bootCount;///<Количество успешных включений.
    Motherboard* motherboard;///<Указатель на материнскую плату.
    PSU* psu;///<Указатель на блок питания.
    OperatingSystem* os;///<Указатель на установленную операционную систему.
    std::vector<Storage*> storages;///<Вектор установленных накопителей.

public:
/**
 * @brief Конструктор по умолчанию.
 * Создает ПК с пустым именем и нулевыми указателями.
 */
    Computer();

/**
 * @brief Конструктор с указанием имени.
 * @param hostname Сетевое имя компьютера.
 */
    explicit Computer(const std::string& hostname);

/**
 * @brief Виртуальный деструктор по умолчанию.
 */
    virtual ~Computer()=default;

/**
 * @brief Собирает компьютер, устанавливая материнскую плату и блок питания.
 * @param board Указатель на материнскую плату.
 * @param supply Указатель на блок питания.
 */
    void assemble(Motherboard* board,PSU* supply);

/**
 * @brief Добавляет накопитель в систему.
 * @param storage Указатель на объект накопителя.
 */
    void addStorage(Storage* storage);

/**
 * @brief Устанавливает операционную систему.
 * @param newOs Указатель на устанавливаемую ОС.
 * @exception InvalidConfigurationException если в системе нет ни одного накопителя.
 */   
    void installOs(OperatingSystem* newOs);

/**
 * @brief Включает компьютер.
 * @exception BootFailureException если компьютер не собран (нет платы или БП).
 * @exception InsufficientPowerException если мощности БП недостаточно.
 */   
    void powerOn();

/**
 * @brief Вычисляет общий объем свободного места на всех накопителях.
 * @return Суммарное свободное место в гигабайтах.
 */
    int freeStorageGb();

/**
 * @brief Вычисляет текущее энергопотребление компьютера.
 * @return Потребляемая мощность в ваттах. Может быть переопределен в наследниках.
 */  
    virtual int powerDraw();

/**
 * @brief Вычисляет резерв мощности блока питания.
 * @return Разница между мощностью БП и текущим потреблением (в ваттах).
 * @exception BootFailureException если блок питания не установлен.
 */
    int powerReserve();
};
