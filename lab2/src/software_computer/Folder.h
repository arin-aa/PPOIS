/**
 * @file Folder.h
 * @brief Объявление класса Folder.
 */
#pragma once
#include <vector>

class File;

/**
 * @class Folder
 * @brief Класс папки, содержащей файлы.
 */
class Folder{
private:
    int freeMb;///<Свободное место в папке в МБ.
    std::vector<File*> files;///<Список файлов в папке.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Folder();

/**
 * @brief Конструктор с указанием свободного места.
 * @param freeMb Начальное свободное место в МБ.
 */
    explicit Folder(int freeMb);

/**
 * @brief Добавляет файл в папку.
 * @param file Указатель на файл.
 * @exception DiskFullException если файл не помещается в папку.
 */
    void addFile(File* file);

/**
 * @brief Считает общее количество страниц во всех файлах папки.
 * @return Суммарное количество страниц.
 */
    int totalPages();
};
