# PPOIS


Лабораторные работы по курсу ППОИС.


## Структура


| Лаба | Язык | Содержание | Документация |
|------|------|------------|--------------|
| 1 | C++ | CantorSet, TicTacToe | [set](https://arin-aa.github.io/PPOIS/lab_1/set/), [tictactoe](https://arin-aa.github.io/PPOIS/lab_1/tictactoe/) |
| 2 | C++ | Computer | [computer](https://arin-aa.github.io/PPOIS/lab_2/) |


## Требования


- Компилятор с поддержкой C++17 (GCC 9+, Clang 10+, MSVC 2019+)
- [Catch2](https://github.com/catchorg/Catch2) (v3) — библиотека для unit-тестов
- `lcov` и `gcov` — для проверки покрытия кода
- `cppcheck` — для статического анализа
- Doxygen — для пересборки документации (опционально)


## Документация


Сгенерирована с помощью [Doxygen](https://www.doxygen.nl/) и опубликована через [GitHub Pages](https://pages.github.com/):


- [Главная страница со списком всех лабораторных](https://arin-aa.github.io/PPOIS/)


## Релизы


Готовые бинарники для Linux (собранные автоматически) публикуются в [Releases](https://github.com/arin-aa/PPOIS/releases):
- `cantorset` — Лаба 1 (Множество)
- `tictactoe` — Лаба 1 (Крестики-нолики)
- `lab2_computer` — Лаба 2 (Компьютер)


## CI/CD


На каждый push и Pull Request запускается [CI/CD пайплайн](https://github.com/arin-aa/PPOIS/actions), который автоматически:


- собирает CLI для всех трех проектов;
- запускает unit-тесты (с использованием Catch2);
- проверяет покрытие кода (требование: ≥ 90%, с генерацией отчета `lcov`);
- проводит статический анализ кода (линтер `cppcheck`);
- собирает бинарники и публикует их в Releases при пуше в ветку `main`.