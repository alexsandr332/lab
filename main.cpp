#include "sport2.h"
#include <iostream>
#include <limits>

void show_menu() {
    std::cout << "\n=== СПОРТИВНАЯ БАЗА ДАННЫХ ===\n";
    std::cout << "1. Добавить матч\n";
    std::cout << "2. Показать все матчи\n";
    std::cout << "3. Удалить матч\n";
    std::cout << "4. Сохранить в файл\n";
    std::cout << "5. Загрузить из файла\n";
    std::cout << "6. Поиск по команде\n";
    std::cout << "7. Поиск по месту\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    MatchDB db;
    int choice, id;
    
    do {
        show_menu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                if (db.add_match())
                    std::cout << "Матч добавлен!\n";
                break;
                
            case 2:
                db.show_all();
                break;
                
            case 3:
                std::cout << "ID матча для удаления: ";
                std::cin >> id;
                std::cin.ignore();
                if (db.delete_match(id))
                    std::cout << "Матч удалён!\n";
                else
                    std::cout << "Матч с ID " << id << " не найден\n";
                break;
                
            case 4:
                db.save_db();
                std::cout << "Сохранено в sport.dat\n";
                break;
                
            case 5:
                db.load_db();
                std::cout << "Загружено из sport.dat\n";
                break;
                
            case 6:
                db.search_team();
                break;
                
            case 7:
                db.search_place();
                break;
                
            case 0:
                std::cout << "До свидания!\n";
                break;
                
            default:
                std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
    
    return 0;
}
