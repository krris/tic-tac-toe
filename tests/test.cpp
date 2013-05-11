#include <boost/test/minimal.hpp>
#include <log4cxx/basicconfigurator.h>
#include <iostream>

#define private public

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
    std::string player_mark = "blabla";
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
    BOOST_CHECK (status.draw(grid) == false);

    for (Row row: status.getWinningDiagonals())
    {
        for (Move move: row)
        {
            std::cout << "(" << move.first << ", " << move.second << ")" << std::endl;
        }
    } 





    BOOST_CHECK (status.winner(grid, player_mark) == false);
   // BOOST_CHECK (status.winner(grid, std::make_pair(0,0), ai_mark) == true);
   // BOOST_CHECK (status.winner(grid, player_mark) != true);



    return 0;
}
