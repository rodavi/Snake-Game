#ifndef SCORES_H
#define SCORES_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <iostream>
#include <sstream> 
#include <algorithm>
struct Player{
    std::string name;
    int score;
};

class Scores{

public:
    Scores(){}
    std::vector<Player> getScores(const std::string& path);
    void setScores(Player& p);
    Player getBest();
    Player getLast();
    void printScores();
private:
    
    std::fstream _file;
    std::vector<Player> _scores;
    std::string _path;
    int new_score{0};
    std::string new_player;
    size_t top_count{3};
};
#endif