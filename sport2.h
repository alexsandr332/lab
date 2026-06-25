#ifndef SPORT2_H
#define SPORT2_H

#include <string>
#include <cstring>

struct Match {
    int id;
    std::string team1;
    std::string team2;
    std::string place;
    int score1;
    int score2;
    int viewers;
    float cost;
};

class MatchDB {
private:
    Match* data;
    int capacity;
    int size;
    int next_id;
    std::string filename;

    void resize();

public:
    MatchDB();
    explicit MatchDB(const std::string& fname);
    MatchDB(const MatchDB& other);
    MatchDB& operator=(const MatchDB& other);
    ~MatchDB();
    
    void inputMatch(Match& m);
    bool add_match();
    void show_all() const;
    bool delete_match(int id);
    void save_db() const;
    void load_db();
    void search_team() const;
    void search_place() const;
    
    int get_count() const { return size; }
    void set_filename(const std::string& fname) { filename = fname; }
};

#endif
