#include "Set.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
const int MAX_IGNOR=100000;
using namespace std;

int readChoice(const string& text){
    int choice;
    while (true) {
        cout << text;
        if (cin >> choice) {
            cin.clear();cin.ignore(MAX_IGNOR, '\n');
            return choice;
        }
        cin.clear(); cin.ignore(MAX_IGNOR, '\n');
        cout << "Некорректный ввод. Попробуйте снова.\n";
    }
}

CantorSet& chooseSet(CantorSet& A, CantorSet& B){
    while(true){
        cout<<"Выберите множество (A/B): ";
        string line;
        getline(cin,line);
        if(line=="A" || line=="a"){
            return A;
        }
        if(line=="B" || line=="b"){
            return B;
        }
        cout<<"Некорректный ввод. Попробуйте снова.\n";
    }
}


string readElem(const string& line) {
    while(true){
        cout<<line;
        string symbols;
        getline(cin,symbols);
        bool correct = !symbols.empty();
        for(char symbol: symbols){
            if(!isalnum(static_cast<unsigned char>(symbol))){
                correct=false;
                break;
            }
        }
        if(correct){
            return symbols;
        }
        cout<<"Ошибка: некорректный ввод.\n";
    }
}

int main(){
    CantorSet A;
    CantorSet B;
    while(true){
        cout<<"Меню\n"<<"1 - Ввести множество A.\n"<<"2 - Ввести множество B.\n"<<"3 - Показать множества A и B.\n"<<"4 - Добавить элемент.\n"<<"5 - Добавить подмножество.\n"
        <<"6 - Удалить элемент.\n"<<"7 - Удалить подмножество.\n"<<"8 - Проверить пустоту.\n"<<"9 - Мощность.\n"
        <<"10 - Элемент принадлежит множеству.\n"<<"11 - Подмножество принадлежит множеству.\n"<<"12 - Булеан.\n"<<"13 - Объединение.\n"<<"14 - Пересечение.\n"<<"15 - Разность.\n"<<"16 - Выход.\n";
        int keys=readChoice("Ваш выбор: ");
        cout<<endl;
        try{
            switch(keys){
                case 1:{
                    cout<<"Введите множество A: ";
                    cin>>A;
                    cout<<"A = "<<A<<endl;
                    break;
                }

                case 2:{
                    cout<<"Введите множество B: ";
                    cin>>B;
                    cout<<"B = "<<B<<endl;
                    break;
                }

                case 3:{
                    cout<<"A = "<<A<<endl;
                    cout<<"B = "<<B<<endl;
                    break;
                }

                case 4:{
                    CantorSet& set=chooseSet(A,B);
                    string elem=readElem("Введите елемент: ");
                    if(set.addElement(elem)){
                        cout<<"Элемент добавлен.\n";
                    }
                    else{
                        cout<<"Ошибка. Такой элемент уже есть.\n";
                    }
                    break;
                }

                case 5:{
                    CantorSet& set=chooseSet(A,B);
                    cout<<"Введите подмножество: ";
                    CantorSet sub;
                    cin>>sub;
                    if(set.addSubset(sub)){
                        cout<<"Подмножество добавлено.\n";
                    }
                    else{
                        cout<<"Ошибка. Такое подмножество уже есть.\n";
                    }
                    break;
                }

                case 6:{
                    CantorSet& set=chooseSet(A,B);
                    string elem=readElem("Введите элемент: ");
                    if(set.delElement(elem)){
                        cout<<"Элемент удалён.\n";
                    }
                    else{
                        cout<<"Ошибка. Такой элемент не найден.\n";
                    }
                    break;
                }

                case 7:{
                    CantorSet& set=chooseSet(A,B);
                    cout<<"Введите подмножество: ";
                    CantorSet sub;
                    cin>>sub;
                    if(set.delSubset(sub)){
                        cout<<"Подмножество удалено.\n";
                    }
                    else{
                        cout<<"Ошибка. Такое подмножество не найдено.\n";
                    }
                    break;
                }

                case 8:{
                    CantorSet& set=chooseSet(A,B);
                    if(set.isEmpty()){
                        cout<<"Множество пустое.\n";
                    } 
                    else{
                        cout<<"Множество не пустое.\n";
                    }
                    break;
                }

                case 9:{
                    CantorSet& set=chooseSet(A,B);
                    cout<<"Мощность = "<<set.power()<<"\n";
                    break;
                }

                case 10:{
                    CantorSet& set=chooseSet(A, B);
                    string elem=readElem("Введите элемент: ");
                    if(set[elem]){
                        cout<<"Элемент принадлежит множеству.\n";
                    } 
                    else{
                        cout<<"Элемент не принадлежит множеству.\n";
                    }
                    break;
                }

                case 11:{
                    CantorSet& set=chooseSet(A, B);
                    cout<<"Введите подмножество: ";
                    CantorSet sub;
                    cin>>sub;
                    if(set[sub]){
                        cout<<"Подмножество принадлежит множеству.\n";
                    } 
                    else{
                        cout<<"Подмножество не принадлежит множеству.\n";
                    }
                    break;
                }

                case 12:{
                    CantorSet& set=chooseSet(A,B);
                    CantorSet bul=set.bulean();
                    cout<<"Булеан: "<<bul<<"\n";
                    break;
                }

                case 13:{
                    cout<<"1 - A+=B.\n"<<"2 - A+B.\n";
                    int choice=readChoice("Выберите способ записи: ");
                    if(choice==1){
                        A+=B;
                        cout<<"Результат: "<<A<<endl;
                    }
                    else if(choice==2){
                        CantorSet newSet=A+B;
                        cout<<"Результат: "<<newSet<<endl;
                    }
                    else{
                        cout << "Неверный выбор.\n";
                    }
                    break;
                }

                case 14:{
                    cout<<"1 - A*=B.\n"<<"2 - A*B.\n";
                    int choice=readChoice("Выберите способ записи: ");
                    if(choice==1){
                        A*=B;
                        cout<<"Результат: "<<A<<endl;
                    }
                    else if(choice==2){
                        CantorSet newSet=A*B;
                        cout<<"Результат: "<<newSet<<endl;
                    }
                    else{
                        cout << "Неверный выбор.\n";
                    }
                    break;
                }

                case 15:{
                    cout<<"1 - A-=B.\n"<<"2 - A-B.\n"<<"3 - B-A.\n"<<"4 - B-=A\n";
                    int choice=readChoice("Выберите способ записи: ");
                    if(choice==1){
                        A-=B;
                        cout<<"Результат: "<<A<<endl;
                    }
                    else if(choice==2){
                        CantorSet newSet1=A-B;
                        cout<<"Результат: "<<newSet1<<endl;
                    }
                    else if(choice==3){
                        CantorSet newSet2=B-A;
                        cout<<"Результат: "<<newSet2<<endl;
                    }
                    else if(choice==4){
                        B-=A;
                        cout<<"Результат: "<<B<<endl;
                    }
                    else{
                        cout << "Неверный выбор.\n";
                    }
                    break;
                }

                case 16:{
                    cout<<"Выход.\n";
                    return 0;
                }

                default:{
                    cout<<"Неверный выбор.\n";
                    break;
                }
            }
        }
        catch(const exception& error){
            cout<<"Ошибка: "<<error.what()<<endl;
        }
    }
    return 0;
}