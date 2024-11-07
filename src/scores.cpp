#include "scores.h"

/*Scores::Scores()
{
    _path = std::make_unique<std::string>("../"+path);
    getScores();
}*/

std::vector<Player> Scores::getScores(const std::string& path)
{
    _path = "../"+path;
    std::cout<<_path<<"\n";
    std::string line, player, score;
    _file.open(_path);
    if(_file.is_open())
    {
        std::cout<<"The Top "<<top_count<<" scores are:\n";
        for(size_t i = 0; i<top_count;++i){
            std::getline(_file, line);   // Read every line
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
        printScores();
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

    std::ofstream o_file;
    o_file.open(_path);
    int i = 0;
    for(auto single_score:_scores)
    {
        o_file<<single_score.name<<"="<<single_score.score;
        if(top_count != i-1) {
            o_file<<"\n";
            i++;
        }
    }
    o_file.close();
}

Player Scores::getBest()
{
    return *_scores.begin();
}

Player Scores::getLast()
{
    return _scores[top_count-1];
}

void Scores::printScores()
{
    size_t spot{1};
    for(auto _score:_scores){
        std::cout<<"#"<<spot<<" "<<_score.name<<" -> "<<_score.score<<"\n";
        ++spot;
    }
}