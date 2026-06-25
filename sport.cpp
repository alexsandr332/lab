#include "sport2.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>

MatchDB::MatchDB() : data(nullptr), capacity(0), size(0), next_id(1), filename("sport.dat") {}

MatchDB::MatchDB(const std::string& fname) 
    : data(nullptr), capacity(0), size(0), next_id(1), filename(fname) {}

MatchDB::MatchDB(const MatchDB& other) 
    : capacity(other.capacity), size(other.size), next_id(other.next_id), filename(other.filename) {
    if (size > 0) {
        data = new Match[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr;
    }
}

MatchDB& MatchDB::operator=(const MatchDB& other) {
    if (this != &other) {
        delete[] data;
        
        capacity = other.capacity;
        size = other.size;
        next_id = other.next_id;
        filename = other.filename;
        
        if (size > 0) {
            data = new Match[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    return *this;
}

MatchDB::~MatchDB() {
    delete[] data;
}

void MatchDB::resize() {
    int new_capacity = (capacity == 0) ? 2 : capacity * 2;
    Match* new_data = new Match[new_capacity];
    
    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void MatchDB::inputMatch(Match& m) {
    std::cout << "Команда 1: ";
    std::getline(std::cin, m.team1);
    
    std::cout << "Команда 2: ";
    std::getline(std::cin, m.team2);
    
    std::cout << "Место: ";
    std::getline(std::cin, m.place);
    
    std::cout << "Счет1: ";
    std::cin >> m.score1;
    std::cout << "Счет2: ";
    std::cin >> m.score2;
    std::cout << "Зрители: ";
    std::cin >> m.viewers;
    std::cout << "Цена: ";
    std::cin >> m.cost;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool MatchDB::add_match() {
    if (size >= capacity) {
        resize();
    }
    
    Match m;
    m.id = next_id++;
    inputMatch(m);
    data[size++] = m;
    return true;
}

void MatchDB::show_all() const {
    std::cout << "\n=== ВСЕ МАТЧИ (" << size << ") ===\n";
    for (int i = 0; i < size; ++i) {
        const Match& m = data[i];
        std::cout << m.id << ". " << m.team1 << " - " << m.team2 
                  << " " << m.score1 << ":" << m.score2 
                  << " [" << m.place << "] зрители:" << m.viewers 
                  << " цена:" << m.cost << "\n";
    }
}

bool MatchDB::delete_match(int id) {
    for (int i = 0; i < size; ++i) {
        if (data[i].id == id) {
            for (int j = i; j < size - 1; ++j) {
                data[j] = data[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

void MatchDB::save_db() const {
    std::ofstream f(filename.c_str(), std::ios::binary);
    if (!f) {
        std::cerr << "Ошибка открытия файла " << filename << " для записи!\n";
        return;
    }
    
    f.write(reinterpret_cast<const char*>(&size), sizeof(int));
    f.write(reinterpret_cast<const char*>(&next_id), sizeof(int));
    
    for (int i = 0; i < size; ++i) {
        const Match& m = data[i];
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
    std::ifstream f(filename.c_str(), std::ios::binary);
    if (!f) {
        std::cerr << "Файл " << filename << " не найден!\n";
        return;
    }
    
    int loaded_size, loaded_next_id;
    f.read(reinterpret_cast<char*>(&loaded_size), sizeof(int));
    f.read(reinterpret_cast<char*>(&loaded_next_id), sizeof(int));
    
    delete[] data;
    data = nullptr;
    capacity = 0;
    size = 0;
    
    if (loaded_size > 0) {
        capacity = loaded_size * 2;
        data = new Match[capacity];
        
        for (int i = 0; i < loaded_size; ++i) {
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
            
            data[size++] = m;
        }
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
    for (int i = 0; i < size; ++i) {
        const Match& m = data[i];
        if (m.team1.find(name) != std::string::npos || 
            m.team2.find(name) != std::string::npos) {
            std::cout << m.id << ". " << m.team1 << " - " << m.team2 
                      << " " << m.score1 << ":" << m.score2 << "\n";
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
    for (int i = 0; i < size; ++i) {
        const Match& m = data[i];
        if (m.place.find(place) != std::string::npos) {
            std::cout << m.id << ". " << m.team1 << " - " << m.team2 
                      << " в " << m.place << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "Не найдено\n";
}
