// sport.cpp
#include "sport.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <limits>

MatchDB::MatchDB() : next_id(1) {}

void MatchDB::inputMatch(Match& m) {
    std::cout << "Команда 1: ";
    std::getline(std::cin, m.team1);
    
    std::cout << "Команда 2: ";
    std::getline(std::cin, m.team2);
    
    std::cout << "Место: ";
    std::getline(std::cin, m.place);
    
    std::cout << "Счет1 Счет2 Зрители Цена: ";
    std::cin >> m.score1 >> m.score2 >> m.viewers >> m.cost;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool MatchDB::add_match() {
    Match m;
    m.id = next_id++;
    inputMatch(m);
    data.push_back(m);
    return true;
}

void MatchDB::show_all() const {
    std::cout << "\n=== ВСЕ МАТЧИ (" << data.size() << ") ===\n";
    for (const auto& m : data) {
        std::cout << m.id << ". " << m.team1 << " - " << m.team2 
                  << " " << m.score1 << ":" << m.score2 
                  << " [" << m.place << "] зрители:" << m.viewers 
                  << " цена:" << m.cost << "\n";
    }
}

bool MatchDB::delete_match(int id) {
    auto it = std::find_if(data.begin(), data.end(), 
                           [id](const Match& m) { return m.id == id; });
    if (it != data.end()) {
        data.erase(it);
        return true;
    }
    return false;
}

void MatchDB::save_db() const {
    std::ofstream f("sport.dat", std::ios::binary);
    if (!f) return;
    
    int count = data.size();
    f.write(reinterpret_cast<const char*>(&count), sizeof(int));
    f.write(reinterpret_cast<const char*>(&next_id), sizeof(int));
    
    for (const auto& m : data) {
        int len1 = m.team1.size() + 1;
        int len2 = m.team2.size() + 1;
        int len3 = m.place.size() + 1;
        
        f.write(reinterpret_cast<const char*>(&len1), sizeof(int));
        f.write(m.team1.c_str(), len1);
        f.write(reinterpret_cast<const char*>(&len2), sizeof(int));
        f.write(m.team2.c_str(), len2);
        f.write(reinterpret_cast<const char*>(&len3), sizeof(int));
        f.write(m.place.c_str(), len3);
        
        f.write(reinterpret_cast<const char*>(&m.id), sizeof(int));
        f.write(reinterpret_cast<const char*>(&m.score1), sizeof(int));
        f.write(reinterpret_cast<const char*>(&m.score2), sizeof(int));
        f.write(reinterpret_cast<const char*>(&m.viewers), sizeof(int));
        f.write(reinterpret_cast<const char*>(&m.cost), sizeof(float));
    }
    
    f.close();
}

void MatchDB::load_db() {
    std::ifstream f("sport.dat", std::ios::binary);
    if (!f) return;
    
    int count, loaded_next_id;
    f.read(reinterpret_cast<char*>(&count), sizeof(int));
    f.read(reinterpret_cast<char*>(&loaded_next_id), sizeof(int));
    
    data.clear();
    data.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        Match m;
        int len;
        
        f.read(reinterpret_cast<char*>(&len), sizeof(int));
        char* buf = new char[len];
        f.read(buf, len);
        m.team1 = buf;
        delete[] buf;
        
        f.read(reinterpret_cast<char*>(&len), sizeof(int));
        buf = new char[len];
        f.read(buf, len);
        m.team2 = buf;
        delete[] buf;
        
        f.read(reinterpret_cast<char*>(&len), sizeof(int));
        buf = new char[len];
        f.read(buf, len);
        m.place = buf;
        delete[] buf;
        
        f.read(reinterpret_cast<char*>(&m.id), sizeof(int));
        f.read(reinterpret_cast<char*>(&m.score1), sizeof(int));
        f.read(reinterpret_cast<char*>(&m.score2), sizeof(int));
        f.read(reinterpret_cast<char*>(&m.viewers), sizeof(int));
        f.read(reinterpret_cast<char*>(&m.cost), sizeof(float));
        
        data.push_back(m);
    }
    
    next_id = loaded_next_id;
    f.close();
}

void MatchDB::search_team() const {
    std::string name;
    std::cout << "Название команды: ";
    std::getline(std::cin, name);
    
    std::cout << "\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n";
    bool found = false;
    for (const auto& m : data) {
        if (m.team1.find(name) != std::string::npos || 
            m.team2.find(name) != std::string::npos) {
            std::cout << m.id << ". " << m.team1 << " - " << m.team2 << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "Не найдено\n";
}

void MatchDB::search_place() const {
    std::string place;
    std::cout << "Место проведения: ";
    std::getline(std::cin, place);
    
    std::cout << "\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n";
    bool found = false;
    for (const auto& m : data) {
        if (m.place.find(place) != std::string::npos) {
            std::cout << m.id << ". " << m.team1 << " - " << m.team2 
                      << " в " << m.place << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "Не найдено\n";
}
