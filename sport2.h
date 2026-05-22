#ifndef SPORT_H
#define SPORT_H

#include <string>
#include <vector>

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
    std::vector<Match> data;
    int next_id;

public:
    MatchDB();
    
    void inputMatch(Match& m);
    bool add_match();
    void show_all() const;
    bool delete_match(int id);
    void save_db() const;
    void load_db();
    void search_team() const;
    void search_place() const;
    
    int get_count() const { return data.size(); }
};

#endif
