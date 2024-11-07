#include "scores.h"

Scores::Scores(const std::string& path)
{
    _path = std::make_unique<std::string>("../"+path);
    getScores();
}

std::vector<Player> Scores::getScores()
{
    std::string line, player, score;
    _file.open(*_path);
    if(_file.is_open())
    {
        std::cout<<"The Top 3 scores are:\n";
        while(std::getline(_file, line))    // Read every line
        {
            std::replace(line.begin(), line.end(), '=', ' ');   //replace the '=' with whitespace
            std::istringstream stream(line);
            while(stream>> player >> score)
            {
                Player p;
                p.name = player;
                p.score = std::stoi(score); //change string to int
                _scores.push_back(p);   // add the player to the vector
            }
        }
        _file.close();
        std::sort(_scores.begin(), _scores.end(), 
        [](Player& a, Player& b){return a.score>b.score;}); //sort the players base on their score
    }
    else std::cout<<"File unable to open!\n";

    return _scores;
}

void Scores::setScores(Player& p)
{
    _scores.push_back(p);
    std::sort(_scores.begin(), _scores.end(), 
        [](Player& a, Player& b){return a.score>b.score;}); //sort the players base on their score
    _scores.erase(_scores.end());   //stay with only 3 spots
}

Player Scores::getBest()
{
    return *_scores.begin();
}

void Scores::printScores()
{
    size_t spot{1};
    for(auto _score:_scores){
        std::cout<<"#"<<spot<<" "<<_score.name<<" -> "<<_score.score<<"\n";
        ++spot;
    }
}