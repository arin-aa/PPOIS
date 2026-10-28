/**
 * @file RepairTicket.h
 * @brief Объявление класса RepairTicket.
 */
#pragma once
#include <string>

class Computer;
class Technician;

/**
 * @class RepairTicket
 * @brief Класс заявки на ремонт.
 * 
 * Отслеживает жизненный цикл заявки: от создания до назначения техника 
 * и закрытия с расчетом итоговой стоимости.
 */
class RepairTicket{
private:
    std::string description;///<Описание проблемы.
    std::string status;///<Текущий статус ("open", "assigned", "closed").
    int hoursSpent;///<Количество затраченных часов.
    Computer* computer;///<Указатель на ремонтируемый компьютер.
    Technician* technician;///<Указатель на назначенного техника.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    RepairTicket();

/**
 * @brief Конструктор с параметрами.
 * @param description Описание проблемы.
 * @param computer Указатель на компьютер.
 */
    RepairTicket(const std::string& description,Computer* computer);

/**
 * @brief Назначает техника на выполнение заявки.
 * @param worker Указатель на техника.
 * @exception InvalidConfigurationException если заявка уже назначена или закрыта.
 */
    void assign(Technician* worker);

/**
 * @brief Проводит диагностику компьютера.
 * @return Оставшийся резерв мощности блока питания.
 */
    int diagnose();

/**
 * @brief Закрывает заявку и рассчитывает стоимость.
 * @param hours Количество затраченных часов.
 * @return Итоговая стоимость ремонта.
 * @exception UnauthorizedAccessException если на заявку не назначен техник.
 */
    int close(int hours);
};
