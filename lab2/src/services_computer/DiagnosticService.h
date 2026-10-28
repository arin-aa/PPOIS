/**
 * @file DiagnosticService.h
 * @brief Объявление класса DiagnosticService.
 */
#pragma once

class Logger;
class Computer;

/**
 * @class DiagnosticService
 * @brief Сервис диагностики компьютера.
 * 
 * Проверяет состояние системы на наличие проблем с питанием и дисковым пространством, 
 * логирует их и вычисляет общий показатель состояния.
 */
class DiagnosticService{
private:
    int issuesFound;///<Общее количество найденных проблем.
    int lowReserveWatts;///<Порог низкого резерва мощности.
    int lowDiskGb;///<Порог низкого свободного места.
    Logger* logger;///<Указатель на объект логгера.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    DiagnosticService();

/**
 * @brief Конструктор с параметрами.
 * @param lowReserveWatts Порог резерва мощности.
 * @param lowDiskGb Порог свободного места.
 * @param logger Указатель на логгер.
 */
    DiagnosticService(int lowReserveWatts,int lowDiskGb,Logger* logger);

/**
 * @brief Сканирует компьютер на наличие проблем.
 * @param computer Указатель на проверяемый компьютер.
 * @return Общее количество найденных проблем на текущий момент.
 */
    int scan(Computer* computer);

/**
 * @brief Вычисляет показатель состояния системы.
 * @return Оценка от 0 до 100 (каждая проблема снижает оценку на 25 баллов).
 */ 
    int healthScore();
};
