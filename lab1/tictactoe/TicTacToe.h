/**
 * @file TicTacToe.h
 * @brief Объявление класса TicTacToe и перечисления Cell.
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <iostream>
#include <utility>

/**
 * @brief Возможные состояния ячейки игрового поля.
 */
enum class Cell: char{
    cross='X',///<Ячейка занята крестиком.
    nought='O',///<Ячейка занята ноликом.
    empty=' '///<Ячейка свободна.
};

/**
 * @class TictacToe
 * @brief Класс реализует логику игры "Крестики-нолики" 
 * на квадратном поле size*size произвольного размера. 
 * Поддерживает ходы двух игроков, проверку победы и ничьей, вывод доски на консоль.
 */

class TicTacToe{
    private:
    int size;///<Размер игрового поля.
    std::vector<std::vector<Cell>> board;///<Двумерный массив ячеек.
    Cell winner;///<Победитель; Cell::empty, если еще не определён.
    Cell currentPlayer;///<Текущий игрок; по умолчанию - крестик.

    public:
    /**
     * @brief Конструктор по умолчанию
     * @param newSize Размер игрового поля (по умолчанию 3*3).
     * 
     * Создаёт поле newSize*newSize, заполненное пустыми ячейками.
     * Первым ходит игрок, играющий за крестик.
     */
    TicTacToe(int newSize=3);

    /**
     * @brief Доступ к ячейке поля по координатам.
     * @param position Пара координат (строка, столбец).
     * @return Константная ссылка на содержимое ячейки. 
     */
    const Cell& operator[](std::pair<int,int> position)const;

    /**
     * @brief Проверяет, находятся ли координаты в пределах игрового поля.
     * @param row Индекс строки.
     * @param column Индекс столбца.
     * @return true, если координаты корректны, иначе false.
     */
    bool inRange(int row,int column)const;

    /**
     * @brief Выполняет ход текущего игрока.
     * @param row Индекс строки.
     * @param column Индекс столбца.
     * @exception std::out_of_range если координаты вне поля.
     * @exception std::invalid_argument если клетка уже занята.
     * 
     * После хода проверяется условие победы, если победы нет,
     * право хода переходит другому игроку.
     */
    void makeMove(int row,int column);

    /**
     * @brief Поверяет, есть ли у игрока выигрышная линия.
     * @param player Игрок, ход которого проверяется на победу.
     * @return true, если найдена выигрышная строка, столбец, основная или побочная диагональ.
     */
    bool checkWin(Cell player)const;

    /**
     * @brief Проверяет, завершилась ли игра ничьей.
     * @return true, если поле полностью заполнено значениями и победителя нет. 
     */
    bool isDraw()const;

    /**
     * @brief Проверяет, определён ли победитель.
     * @return true, если победитель есть.
     */
    bool isWon()const;

    /**
     * @brief Возвращает размер игрового поля.
     * @return Размер поля.
     */
    int getSize()const;
        
    /**
     * @brief Возвращает текущего игрока.
     * @return Текущий игрок.
     */
    Cell getCurrentPlayer()const;
        
    /**
     * @brief Возвращает победителя игры.
     * @return Значение крестика или нолика, если победитель определён, иначе пустую ячейку.
     */
    Cell getWinner()const;
        
    /**
     * @brief Выводит текущее состояние игрового поля в поток.
     * @param output Выходной поток.
     * @param game Игра, состояние которой нужно вывести.
     * @return Ссылка на переданный поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& output,const TicTacToe& game);
};
#endif//TICTACTOE_H