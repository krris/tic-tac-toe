#include <boost/test/minimal.hpp>
#include <log4cxx/basicconfigurator.h>

#include "../calc/settings.hpp"
#include "../calc/status.hpp"

using namespace log4cxx;
LoggerPtr logger(Logger::getRootLogger());

int test_main( int argc, char* argv[] )
{
    BasicConfigurator::configure();
    LOG4CXX_INFO(logger, "Testing the library for python ...");

    // Set default settings for the game
    int grid_size = 3;
    int marks_to_win = 3;
    std::string player_mark = "O";
    std::string ai_mark = "X";

    PSettings pSettings = Settings::getInstance();
    pSettings->initialize(grid_size, grid_size, marks_to_win, player_mark, ai_mark);

    LOG4CXX_INFO(logger, "Settings initialization ...");
    BOOST_CHECK (pSettings->getGridWidth() == grid_size);
    BOOST_CHECK (pSettings->getMarksToWin() == marks_to_win);
    BOOST_CHECK (pSettings->getPlayerMark() == player_mark);
    BOOST_CHECK (pSettings->getAiMark() == ai_mark);

    Status status(pSettings);

    Grid grid = {{"X","X","X"}, 
                 {"" ,"", ""},
                 {"" ,"", ""}};

    BOOST_CHECK (status.winner(grid, ai_mark) == true);







    return 0;
}
