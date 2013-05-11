#include <string>
#include <boost/smart_ptr.hpp>

class Settings;
typedef boost::shared_ptr<Settings> PSettings;

class Settings{
public:
    static PSettings getInstance();
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


