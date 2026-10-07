# PPOIS

Лабораторные работы по курсу ППОИС.

## Структура

| Лаба | Язык | Содержание | Документация |
|------|------|------------|--------------|
| 1 | C++ | CantorSet, TicTacToe | [set](https://arin-aa.github.io/PPOIS/lab_1/set/), [tictactoe](https://arin-aa.github.io/PPOIS/lab_1/tictactoe/) |

## Требования

- Компилятор с поддержкой C++17 (GCC 9+, Clang 10+, MSVC 2019+)
- PowerShell — для запуска тестов на Windows
- Doxygen — для пересборки документации (опционально)

## Документация

Сгенерирована с помощью [Doxygen](https://www.doxygen.nl/) и опубликована через [GitHub Pages](https://pages.github.com/):

- [Лабораторные работы](https://arin-aa.github.io/PPOIS/)

## Релизы

Готовые бинарники для Linux публикуются в [Releases](https://github.com/arin-aa/PPOIS/releases).

## CI/CD

На каждый push и Pull Request запускается [CI/CD пайплайн](https://github.com/arin-aa/PPOIS/actions):

- сборка CLI для обеих задач;
- unit-тесты с покрытием ≥ 90%.
