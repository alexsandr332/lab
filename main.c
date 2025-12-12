#include "sport.h"
#include <stdio.h>

void menu() {
    printf("\n1. Показать\n2. Добавить\n3. Удалить\n7. Сохранить\n0. Выход\nВыбор: ");
}

int main() {
    MatchDB* db = create_db();
    load_db(db);
    
    int choice;
    do {
        menu();
        scanf("%d", &choice);
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: show_all(db); break;
            case 2: 
                if (add_match(db)) printf("Добавлено\n");
                else printf("Ошибка\n");
                break;
            case 3: {
                int id;
                printf("ID для удаления: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                if (delete_match(db, id)) printf("Удалено\n");
                else printf("Не найдено\n");
                break;
            }
            case 7: 
                save_db(db);
                printf("Сохранено\n");
                break;
        }
    } while(choice != 0);
    
    save_db(db);
    free_db(db);
    return 0;
}
