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
    Scores(const std::string& path);

    std::vector<Player> getScores();
    void setScores(Player& p);
    Player getBest();
    void printScores();
private:
    
    std::fstream _file;
    std::vector<Player> _scores;
    std::unique_ptr<std::string> _path;
    int new_score{0};
    std::string new_player;
};