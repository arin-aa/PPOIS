/**
 * @file Set.h
 * @brief Объявление класса CantorSet.
 */
#ifndef SET_H
#define SET_H
#include <cstddef>
#include <iostream>
#include <vector>
#include <set> 
#include <memory>          
#include <string>                     

/**
 * @class CantorSet
 * @brief Класс реализует канторовское множество, то есть множество,
 * элементами которого могут быть как строки, так и другие множества.
 *
 * Элементы хранятся в упорядоченном std::set без повторений, допускаются только
 * буквы и цифры. Вложенные множества хранятся как вектор умных указателей,
 * отсортированный и без дубликатов. Поддерживает добавление и удаление элементов и подмножеств,
 * проверку принадлежности, объединение, пересечение, разность, построение булеана,
 * а также ввод и вывод в виде строки вида {a, b, {c, d}}.
 */
class CantorSet{
    private:
    std::set<std::string> element;///<Атомарные элементы множества (без повторений).
    std::vector<std::shared_ptr<CantorSet>> subset;///<Вложенные подмножества

    /**
     * @brief Сортирует вектор подмножеств.
     *
     * Порядок определяется оператором operator<. Вызывается после каждого изменения вектора подмножеств.
     */
    void sortSubset();
    
    /**
     * @brief Пропускает пробельные символы в строке.
     * @param symbol Разбираемая строка.
     * @param pos Текущая позиция в строке; после вызова указывает на первый непробельный символ.
     */
    static void skipSpace(const std::string& symbol,std::size_t& pos);

    /**
     * @brief Рекурсивно разбирает множество из строки, начиная с позиции pos.
     * @param symbol Разбираемая строка.
     * @param pos Текущая позиция в строке; после вызова указывает на символ после закрывающей скобки.
     * @return Разобранное множество.
     * @exception std::runtime_error если в строке нарушен синтаксис: нет открывающей
     * или закрывающей скобки, встречен недопустимый символ или отсутствует ',' или '}'.
     */
    static CantorSet parseSet(const std::string& symbol,std::size_t& pos);

    public:
     /**
     * @brief Проверяет, пусто ли множество.
     * @return true, если во множестве нет ни элементов, ни подмножеств.
     */
    bool isEmpty()const;

    /**
     * @brief Добавляет атомарный элемент во множество.
     * @param value Добавляемый элемент.
     * @return true, если элемент добавлен; false, если строка пустая или такой элемент уже есть.
     */
    bool addElement(const std::string& value);

    /**
     * @brief Сравнивает множества для упорядочивания.
     * @param other Множество, с которым выполняется сравнение.
     * @return true, если текущее множество меньше other.
     *
     * Сначала сравниваются атомарные элементы, затем количество подмножеств,
     * затем сами подмножества попарно.
     */
    bool operator<(const CantorSet& other)const;

    /**
     * @brief Проверяет неравенство множеств.
     * @param other Множество, с которым выполняется сравнение.
     * @return true, если множества различаются.
     */
    bool operator!=(const CantorSet& other)const;

    /**
     * @brief Проверяет равенство множеств.
     * @param other Множество, с которым выполняется сравнение.
     * @return true, если совпадают атомарные элементы и все вложенные подмножества.
     */
    bool operator==(const CantorSet& other)const;

    /**
     * @brief Добавляет подмножество во множество.
     * @param sub Добавляемое подмножество.
     * @return true, если подмножество добавлено; false, если равное ему подмножество уже есть.
     *
     * После добавления вектор подмножеств сортируется.
     */
    bool addSubset(const CantorSet& sub);

    /**
     * @brief Проверяет, принадлежит ли элемент множеству.
     * @param value Искомый элемент.
     * @return true, если элемент принадлежит множеству.
     */
    bool operator[](const std::string& value)const;

    /**
     * @brief Проверяет, принадлежит ли подмножество множеству.
     * @param set_ Искомое подмножество.
     * @return true, если подмножество принадлежит множеству.
     */
    bool operator[](const CantorSet& set_)const;

    /**
     * @brief Удаляет элемент из множества.
     * @param value Удаляемый элемент.
     * @return true, если элемент был найден и удалён.
     */
    bool delElement(const std::string& value);

    /**
     * @brief Удаляет подмножество из множества.
     * @param sub Удаляемое подмножество.
     * @return true, если подмножество было найдено и удалено.
     */
    bool delSubset(const CantorSet& sub);

    /**
     * @brief Возвращает мощность множества.
     * @return Суммарное количество атомарных элементов и подмножеств, входящих во множество.
     */
    std::size_t power()const;

    /**
     * @brief Объединение множеств с присваиванием (A+=B).
     * @param other Множество, элементы которого добавляются в текущее.
     * @return Ссылка на изменённое текущее множество.
     */
    CantorSet& operator+=(const CantorSet& other);

    /**
     * @brief Объединение множеств (A+B).
     * @param other Второе множество.
     * @return Новое множество, содержащее элементы и подмножества обоих множеств.
     */
    CantorSet operator+(const CantorSet& other)const;

    /**
     * @brief Пересечение множеств с присваиванием (A*=B).
     * @param other Множество, с которым выполняется пересечение.
     * @return Ссылка на изменённое текущее множество.
     *
     * Остаются только те элементы и подмножества, которые есть и в other.
     */
    CantorSet& operator*=(const CantorSet& other);

    /**
     * @brief Пересечение множеств (A*B).
     * @param other Второе множество.
     * @return Новое множество, содержащее общие элементы и подмножества.
     */
    CantorSet operator*(const CantorSet& other)const;

    /**
     * @brief Разность множеств с присваиванием (A-=B).
     * @param other Множество, элементы которого вычитаются из текущего.
     * @return Ссылка на изменённое текущее множество.
     */
    CantorSet& operator-=(const CantorSet& other);

     /**
     * @brief Разность множеств (A-B).
     * @param other Вычитаемое множество.
     * @return Новое множество с элементами и подмножествами текущего, которых нет в other.
     */
    CantorSet operator-(const CantorSet& other)const;

    /**
     * @brief Строит булеан (множество всех подмножеств).
     * @return Множество, элементами которого являются все подмножества текущего множества,
     * включая пустое и само множество.
     *
     * Для множества мощности n результат содержит 2^n подмножеств.
     */
    CantorSet bulean()const;  
    
    /**
     * @brief Выводит множество в поток в виде {a, b, {c, d}}.
     * @param output Выходной поток.
     * @param symbol Множество, которое нужно вывести.
     * @return Ссылка на переданный поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& output,const CantorSet& symbol);

    /**
     * @brief Считывает множество из потока.
     * @param input Входной поток.
     * @param symbol Множество, в которое записывается результат.
     * @return Ссылка на переданный поток ввода.
     */
    friend std::istream& operator>>(std::istream& input,CantorSet& symbol);

    /**
     * @brief Создаёт множество из строкового представления.
     * @param text Строка вида {a, b, {c, d}}; допускаются пробелы между символами.
     * @return Разобранное множество.
     * @exception std::runtime_error если строка имеет неверный синтаксис
     * или после закрывающей скобки остались лишние символы.
     */
    static CantorSet fromString(const std::string& text);
 };
#endif//SET_H