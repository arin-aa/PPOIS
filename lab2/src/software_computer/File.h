/**
 * @file File.h
 * @brief Объявление класса File.
 */
#pragma once
#include <string>

/**
 * @class File
 * @brief Класс, представляющий файл в файловой системе.
 */

class File{
private:
    std::string fileName;///<Имя файла.
    int sizeMb;///<Размер файла в МБ.
    bool isReadOnly;///<Флаг режима "только для чтения".
    std::string content;///<Текстовое содержимое файла.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    File();

/**
 * @brief Конструктор с параметрами.
 * @param fileName Имя файла.
 * @param sizeMb Размер в МБ.
 * @param isReadOnly Флаг "только для чтения".
 */
    File(const std::string& fileName,int sizeMb,bool isReadOnly);

/**
 * @brief Добавляет текст в конец файла.
 * @param text Добавляемый текст.
 * @exception UnauthorizedAccessException если файл доступен только для чтения.
 */
    void append(const std::string& text);

/**
 * @brief Рассчитывает количество страниц в файле.
 * @return Количество страниц (1 страница = 500 символов).
 */
    int pageCount();

/**
 * @brief Проверяет, помещается ли файл в заданное свободное пространство.
 * @param freeMb Доступное свободное место.
 * @return Оставшееся свободное место после размещения файла.
 * @exception DiskFullException если файл не помещается.
 */
    int fitInto(int freeMb);
};
