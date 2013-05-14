#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <boost/smart_ptr.hpp>

class Settings;
typedef boost::shared_ptr<Settings> PSettings;

/**
 * Holds the settings of a current game.
 * Used a singleton design pattern.
 */
class Settings{
public:
    /**
     * Get an instance of Settings.
     * @return Pointer to Settings 
     */
    static PSettings getInstance();

    /**
     * Initialize settings.
     * @param grid_width Width of the grid
     * @param grid_height Height of the grid
     * @param marks_to_win A number of marks in a row needed to win
     *                     a game.
     * @param player_mark A player's (human) mark: X or O.
     * @param player_mark An AI's mark (computer): X or O.
     */
    void initialize(int grid_width, int grid_height, int marks_to_win,
                    std::string player_mark, std::string ai_mark);
    int getGridWidth();
    int getGridHeight();
    int getMarksToWin();
    std::string getPlayerMark();
    std::string getAiMark();

private:
    Settings() {};
    Settings(const Settings&) {}
    static PSettings pInstance;

    int grid_width;
    int grid_height;
    int marks_to_win;
    std::string player_mark;
    std::string ai_mark;
    
};

#endif
