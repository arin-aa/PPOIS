/**
 * @file Keyboard.h
 * @brief Объявление класса Keyboard.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Keyboard
 * @brief Класс клавиатуры, наследуемый от Peripheral.
 */
class Keyboard:public Peripheral{
private:
    std::string layout;///<Текущая раскладка клавиатуры.
    int keyPresses;///<Счетчик нажатий клавиш.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Keyboard();

/**
 * @brief Конструктор с указанием раскладки.
 * @param layout Начальная раскладка.
 */
    explicit Keyboard(const std::string& layout);

/**
 * @brief Переключает раскладку клавиатуры.
 * @param newLayout Новая раскладка ("EN", "RU", "DE").
 * @exception InvalidConfigurationException если раскладка не поддерживается.
 */
    void switchLayout(const std::string& newLayout);

/**
 * @brief Имитирует нажатие клавиш.
 * @param count Количество нажатий.
 * @return Общее количество нажатий за все время.
 */
    int press(int count);
};
