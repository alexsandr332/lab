#include "sport.h"
#include <stdio.h>

void menu() {
    printf("\n=== БАЗА ДАННЫХ СПОРТИВНЫХ МАТЧЕЙ ===\n");
    printf("1. Показать все матчи\n");
    printf("2. Добавить матч\n");
    printf("3. Удалить матч\n");
    printf("4. Поиск по команде\n");
    printf("5. Поиск по месту\n");
    printf("6. Сохранить в файл\n");
    printf("0. Выход и сохранение\n");
    printf("Выбор: ");
}

int edit_match(MatchDB* db) {
    int id;
    printf("ID для редактирования: ");
    scanf("%d", &id);
    while(getchar() != '\n');
    
    for (int i = 0; i < db->count; i++) {
        if (db->data[i].id == id) {
            printf("Редактирование матча %d\n", id);
            inputMatch(&db->data[i]);
            return 1;
        }
    }
    return 0;
}

int main() {
    MatchDB* db = create_db();
    if (!db) {
        printf("Ошибка создания базы!\n");
        return 1;
    }
    
    load_db(db);
    printf("База загружена. Матчей: %d\n", db->count);
    
    int choice;
    do {
        menu();
        scanf("%d", &choice);
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: 
                show_all(db); 
                break;
            case 2: 
                if (add_match(db)) printf("Матч добавлен!\n");
                else printf("Ошибка добавления\n");
                break;
            case 3: {
                int id;
                printf("ID для удаления: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                if (delete_match(db, id)) printf("Удалено!\n");
                else printf("Не найдено\n");
                break;
            }
            case 4: 
                search_team(db);
                break;
            case 5: 
                search_place(db);
                break;
            case 6: 
                save_db(db);
                printf("Сохранено в файл\n");
                break;
            case 7:
                if (edit_match(db)) printf("Изменено!\n");
                else printf("Не найдено\n");
                break;
        }
    } while(choice != 0);
    
    save_db(db);
    printf("Данные сохранены. Выход.\n");
    free_db(db);
    return 0;
}
