/**
 * @file User.h
 * @brief Объявление базового класса User.
 */
#pragma once
#include <string>

/**
 * @class User
 * @brief Базовый класс пользователя системы.
 * 
 * Содержит логин, пароль и логику аутентификации с защитой от подбора пароля.
 */
class User{
protected:
    std::string login;///<Логин пользователя.
    std::string password;///<Пароль пользователя.
    bool isBlocked;///<Флаг блокировки аккаунта.
    int failedAttempts;///<Счетчик неудачных попыток входа.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    User();

/**
 * @brief Конструктор с параметрами.
 * @param login Логин.
 * @param password Пароль.
 */
    User(const std::string& login,const std::string& password);

/**
 * @brief Виртуальный деструктор по умолчанию.
 */
    virtual ~User()=default;

/**
 * @brief Аутентифицирует пользователя.
 * 
 * При 3-х неудачных попытках подряд аккаунт блокируется.
 * @param candidate Введенный пароль.
 * @return true, если пароль верный.
 * @exception UnauthorizedAccessException если аккаунт заблокирован.
 */
    bool authenticate(const std::string& candidate);

/**
 * @brief Изменяет пароль пользователя.
 * @param oldPassword Старый пароль.
 * @param newPassword Новый пароль.
 * @exception UnauthorizedAccessException если старый пароль неверен или аккаунт заблокирован.
 * @exception InvalidConfigurationException если новый пароль слишком короткий.
 */
    void changePassword(const std::string& oldPassword,const std::string& newPassword);
};
