#include "sport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MatchDB* create_db() {
    MatchDB* db = malloc(sizeof(MatchDB));
    if (!db) return NULL;
    
    db->capacity = 10;
    db->data = malloc(sizeof(Match) * db->capacity);
    db->count = 0;
    db->next_id = 1;
    return db;
}

void free_db(MatchDB* db) {
    if (!db) return;
    free(db->data);
    free(db);
}

void inputMatch(Match* m) {
    printf("Команда 1: ");
    fgets(m->team1, NAME_LEN, stdin);
    m->team1[strcspn(m->team1, "\n")] = 0;
    
    printf("Команда 2: ");
    fgets(m->team2, NAME_LEN, stdin);
    m->team2[strcspn(m->team2, "\n")] = 0;
    
    printf("Место: ");
    fgets(m->place, NAME_LEN, stdin);
    m->place[strcspn(m->place, "\n")] = 0;
    
    printf("Счет1 Счет2 Зрители Цена: ");
    scanf("%d %d %d %f", &m->score1, &m->score2, &m->viewers, &m->cost);
    while(getchar() != '\n');
}

int add_match(MatchDB* db) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        Match* new_data = realloc(db->data, sizeof(Match) * db->capacity);
        if (!new_data) return 0;
        db->data = new_data;
    }
    
    Match* m = &db->data[db->count];
    m->id = db->next_id++;
    inputMatch(m);
    db->count++;
    return 1;
}

void show_all(MatchDB* db) {
    printf("\nВсе матчи (%d):\n", db->count);
    for (int i = 0; i < db->count; i++) {
        printf("%d. %s - %s %d:%d [%s]\n", 
               db->data[i].id,
               db->data[i].team1,
               db->data[i].team2,
               db->data[i].score1,
               db->data[i].score2,
               db->data[i].place);
    }
}

int delete_match(MatchDB* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->data[i].id == id) {
            for (int j = i; j < db->count-1; j++) {
                db->data[j] = db->data[j+1];
            }
            db->count--;
            return 1;
        }
    }
    return 0;
}

void save_db(MatchDB* db) {
    FILE* f = fopen("sport.dat", "wb");
    if (!f) return;
    
    fwrite(&db->count, sizeof(int), 1, f);
    fwrite(&db->next_id, sizeof(int), 1, f);
    fwrite(db->data, sizeof(Match), db->count, f);
    
    fclose(f);
}

void load_db(MatchDB* db) {
    FILE* f = fopen("sport.dat", "rb");
    if (!f) return;
    
    int count, next_id;
    fread(&count, sizeof(int), 1, f);
    fread(&next_id, sizeof(int), 1, f);
    
    if (count > db->capacity) {
        db->capacity = count * 2;
        Match* new_data = realloc(db->data, sizeof(Match) * db->capacity);
        if (new_data) db->data = new_data;
        else { fclose(f); return; }
    }
    
    fread(db->data, sizeof(Match), count, f);
    db->count = count;
    db->next_id = next_id;
    
    fclose(f);
}
