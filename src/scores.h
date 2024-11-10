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
    Scores(std::string path):_path{path}{}
    std::vector<Player> getScores();
    std::vector<Player> getScores(const std::string& path); // It reads a file and return a vector of pairs
    void setScores(Player& p);  // if there is a new top 3 score the player can type its name
    Player getBest();   // returns the best player object
    Player getLast();   // returns the third best player object
    void printScores(); // prints on the console the Top 3 board
private:
    
    std::fstream _file; //used to interact with the file
    std::vector<Player> _scores;    //stores the best scores
    std::string _path;  //stores the path to the text file
    int new_score{0};   //
    std::string new_player;
    size_t top_count{3};
};
#endif