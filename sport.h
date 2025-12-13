#ifndef SPORT_H
#define SPORT_H

#define NAME_LEN 30

typedef struct {
    int id;
    char team1[NAME_LEN];
    char team2[NAME_LEN];
    char place[NAME_LEN];
    int score1;
    int score2;
    int viewers;
    float cost;
} Match;

typedef struct {
    Match* data;
    int count;
    int capacity;
    int next_id;
} MatchDB;

MatchDB* create_db();
void free_db(MatchDB* db);
int add_match(MatchDB* db);
void show_all(MatchDB* db);
int delete_match(MatchDB* db, int id);
void save_db(MatchDB* db);
void load_db(MatchDB* db);
void search_team(MatchDB* db);
void search_place(MatchDB* db);

#endif
