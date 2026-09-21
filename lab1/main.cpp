#include "TicTacToe.h"
#include <iostream>
#include <stdexcept>
const int MAX_IGNOR=100000;
using namespace std;

int readChoice(const string& line){
    int choice;
    while(true){
        cout<<line;
        if(cin>>choice){
            cin.clear(); cin.ignore(MAX_IGNOR,'\n');
            return choice; 
        }
        cin.clear(); cin.ignore(MAX_IGNOR,'\n');
        cout<<"Некорректный ввод. Попробуйте снова.\n";
    }
}

int main(){
    int size=readChoice("Введите размер доски: ");
    if(size<3 || size>10){
        cout<<"Некорректный ввод размера доски. Будет использоваться поле по умолчанию 3*3.\n";
    }
    TicTacToe game=(size>=3 && size<=10)?TicTacToe(size):TicTacToe();
    while(true){
        cout<<"1 - Сделать ход.\n"<<"2 - Посмотреть ячейку по позиции.\n"<<"3 - Выйти.\n";
        int keys=readChoice("Ваш выбор: "); cout<<endl;
        switch(keys){
            case 1:{
                cout<<"Ход игрока "<<static_cast<char>(game.getCurrentPlayer());
                cout<<endl;
                int row=readChoice("Строка: ")-1;
                int column=readChoice("Столбец: ")-1; cout<<endl;
                try{
                    game.makeMove(row,column);
                }
                catch(const exception& error){
                    cout<<"Ошибка: "<<error.what()<<endl;
                    break;
                }
                cout<<game<<endl;
                if(game.isWon()){
                    cout<<"Игра окончена. Выиграл игрок "<<static_cast<char>(game.getWinner())<<".\n";
                    return 0;   
                }
                if(game.isDraw()){
                    cout<<"Игра окончена. Ничья.\n";
                    return 0;
                }
                break;
            }

            case 2:{
                int row,col;
                while(true){
                    row=readChoice("Строка: ")-1;
                    col=readChoice("Столбец: ")-1;
                    if(game.inRange(row,col)){
                        break;
                    }
                    cout<<"Координаты вне диапазона доски. Попробуйте снова.\n";
                }
                Cell cell=game[{row,col}];
                cout<<"В данной клетке: ";
                switch(cell){
                    case Cell::cross: cout<<"крестик.\n"; break;
                    case Cell::nought: cout<<"нолик.\n"; break;
                    case Cell::empty: cout<<"пусто.\n"; break;
                    default: break;
                }
                break;
            }

            case 3:
            cout<<"Выход.\n";
            return 0;

            default:
            cout<<"Неверный выбор.\n";
        }
    }
    return 0;
}