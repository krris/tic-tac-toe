#include "settings.hpp"

Settings* Settings::pInstance = 0l;

Settings* Settings::getInstance()
{
    if (!pInstance)
        pInstance = new Settings;
    return pInstance;
};

void Settings::initialize(int grid_width, int grid_height, int marks_to_win,
                          std::string player_mark, std::string ai_mark)
{
    this->grid_width = grid_width;
    this->grid_height = grid_height;
    this->marks_to_win = marks_to_win;
    this->player_mark = player_mark;
    this->ai_mark = ai_mark;
}

int Settings::getGridWidth()
{
    return this->grid_width;
}

int Settings::getGridHeight()
{
    return this->grid_height;
}

int Settings::getMarksToWin()
{
    return this->marks_to_win;
}

std::string Settings::getPlayerMark()
{
    return this->player_mark;
}

std::string Settings::getAiMark()
{
    return this->ai_mark;
}
