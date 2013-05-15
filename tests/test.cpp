#include <boost/test/minimal.hpp>
#include <log4cxx/basicconfigurator.h>
#include <iostream>

#include "../game/settings.hpp"
#include "../game/status.hpp"
#include "../game/ai.hpp"

using namespace log4cxx;

void testSettigs();
void testStatus();
void testAi();

int test_main( int argc, char* argv[] ) 
{                                       
    BasicConfigurator::configure();  
    LoggerPtr logger(Logger::getRootLogger());
    LOG4CXX_INFO(logger, "Testing the library for python ...");
    LOG4CXX_INFO(logger, "Testing Settings class ...");
    testSettigs();

    LOG4CXX_INFO(logger, "Testing Status class ...");
    testStatus();

    LOG4CXX_INFO(logger, "Testing Ai class ...");
    testAi();
    return 0;
}

void testSettigs()
{
    PSettings settings = Settings::getInstance();
    int grid_width = 10;
    int grid_height = 10;
    int marks_to_win = 5;
    std::string player_mark = "O";
    std::string ai_mark = "X";

    settings->initialize(grid_width, grid_height, marks_to_win, player_mark, ai_mark);
    BOOST_CHECK (settings->getGridWidth() == grid_width);
    BOOST_CHECK (settings->getGridHeight() == grid_height);
    BOOST_CHECK (settings->getMarksToWin() == marks_to_win);
    BOOST_CHECK (settings->getPlayerMark() == player_mark);
    BOOST_CHECK (settings->getAiMark() == ai_mark);

}

void testStatus()
{
    int grid_width = 5;
    int grid_height = 5;
    int marks_to_win = 4;
    std::string player_mark = "X";
    std::string ai_mark = "O";

    PSettings settings = Settings::getInstance();
    settings->initialize(grid_width, grid_height, marks_to_win, player_mark, ai_mark);

    // Test situations where nobody is a winner
    Grid grid = {{"X","","", "", ""},  
                 {"" ,"", "", "", ""} ,
                 {"" ,"", "", "", ""} ,
                 {"" ,"", "", "", ""} ,
                 {"" ,"", "", "", ""} };

    Status status;
    BOOST_CHECK (status.draw(grid) == false);
    BOOST_CHECK (status.winner(grid, player_mark) == false);
    BOOST_CHECK (status.winner(grid, ai_mark) == false);

    for (int x = 0; x < grid_width; ++x)
    {
        for (int y = 0; y < grid_height; ++y)
        {
            Move move = std::make_pair(y, x);
            BOOST_CHECK (status.winner(grid, move, player_mark) == false);
            BOOST_CHECK (status.winner(grid, move, ai_mark) == false);
        }
    }

    // Test situtations where X is a winner
    std::vector<Grid> xWins;
    grid = {{"","X","", "", ""},  
            {"" ,"X", "", "", ""} ,
            {"" ,"X", "", "O", ""} ,
            {"O" ,"X", "O", "", ""} ,
            {"" ,"", "", "", ""} };
    xWins.push_back(grid);
    grid = {{"","X","", "", ""},  
            {"" ,"", "", "", ""} ,
            {"X" ,"X", "X", "X", "X"} ,
            {"O" ,"X", "O", "", ""} ,
            {"" ,"", "", "", ""} };
    xWins.push_back(grid);
    grid = {{"","X","", "X", ""},  
            {"" ,"X", "X", "", ""} ,
            {"" ,"X", "", "O", ""} ,
            {"X" ,"", "O", "", ""} ,
            {"" ,"", "", "", ""} };
    xWins.push_back(grid);
    grid = {{"","","", "", ""},  
            {"X" ,"X", "", "", ""} ,
            {"" ,"X", "", "O", ""} ,
            {"O" ,"X", "X", "", ""} ,
            {"" ,"", "", "X", ""} };
    xWins.push_back(grid);
    grid = {{"","X","", "", ""},  
            {"" ,"X", "", "", ""} ,
            {"" ,"X", "X", "X", "X"} ,
            {"O" ,"", "O", "", ""} ,
            {"" ,"", "", "", ""} };
    xWins.push_back(grid);


    Move move = std::make_pair(2, 1);
    for (Grid g: xWins)
    {
        BOOST_CHECK (status.draw(g) == false);
        BOOST_CHECK (status.winner(g, player_mark) == true);
        BOOST_CHECK (status.winner(g, ai_mark) == false);

        BOOST_CHECK (status.winner(g, move, player_mark) == true);
        BOOST_CHECK (status.winner(g, move, ai_mark) == false);
    }

    std::vector<Grid> oWins;
    //Test situattions where AI is a winner    std::vector<Grid> xWins;
    grid = {{"", "","", "X", ""},  
            {"", "", "", "O", ""} ,
            {"", "", "", "O", ""} ,
            {"", "", "O", "O", ""} ,
            {"", "", "", "O", ""} };
    oWins.push_back(grid);
    grid = {{"", "X","", "", ""},  
            {"" ,"", "", "", ""} ,
            {"" ,"O", "O", "O", "O"} ,
            {"O" ,"X", "O", "", ""} ,
            {"" ,"", "", "", ""} };
    oWins.push_back(grid);
    grid = {{"", "O", "", "X", ""},  
            {"", "X", "O", "", ""} ,
            {"", "X", "", "O", ""} ,
            {"X", "", "O", "", "O"} ,
            {"", "", "", "", ""} };
    oWins.push_back(grid);
    grid = {{"","","", "", ""},  
            {"X" ,"X", "", "", "O"} ,
            {"" ,"", "", "O", ""} ,
            {"O" ,"X", "O", "", ""} ,
            {"" ,"O", "", "X", ""} };
    oWins.push_back(grid);
    grid = {{"","X","", "O", ""},  
            {"" ,"X", "", "O", ""} ,
            {"" ,"", "", "O", ""} ,
            {"O" ,"", "O", "O", ""} ,
            {"" ,"", "", "", ""} };
    oWins.push_back(grid);


    move = std::make_pair(2, 3);
    for (Grid g: oWins)
    {
        BOOST_CHECK (status.draw(g) == false);
        BOOST_CHECK (status.winner(g, player_mark) == false);
        BOOST_CHECK (status.winner(g, ai_mark) == true);

        BOOST_CHECK (status.winner(g, move, player_mark) == false);
        BOOST_CHECK (status.winner(g, move, ai_mark) == true);
    }


    // Test a draw, when a grid is full
    grid = {{"O", "X", "X", "O", "X"},  
            {"O" ,"X", "X", "X", "O"} ,
            {"X" ,"O", "O", "O", "X"} ,
            {"O" ,"X", "O", "O", "X"} ,
            {"X" ,"X", "O", "X", "X"} };
    BOOST_CHECK (status.draw(grid) == true);
}

void testAi()
{
    int grid_width = 3;
    int grid_height = 3;
    int marks_to_win = 3;
    std::string player_mark = "X";
    std::string ai_mark = "O";

    PSettings settings = Settings::getInstance();
    settings->initialize(grid_width, grid_height, marks_to_win, player_mark, ai_mark);

    int max_depth = 9;
    Ai ai(max_depth);

    // Test situations, when "O"s should block "X"s
    // Next ai_mark should be placed in (2,2) (y,x)
    std::vector<Grid> gridsToBlock;
    Grid grid = {{"X","O", ""},  
                 {"O" ,"X", ""} ,
                 {"" ,"", ""} };
    gridsToBlock.push_back(grid);
    grid = {{"","O", "X"},  
            {"O" ,"", "X"} ,
            {"" ,"", ""} };
    gridsToBlock.push_back(grid);
    grid = {{"","O", ""},  
            {"" ,"O", ""} ,
            {"X" ,"X", ""} };
    gridsToBlock.push_back(grid);
    

    for (Grid g : gridsToBlock)
    {
        State state(g, ai_mark, 0);
        State new_state = ai.move(state);
        Move ai_move = new_state.getCrucialMove();
        BOOST_CHECK ( ai_move == std::make_pair(2,2));
    }

    // Test situations, when "O"s should win
    // Next ai_mark should be placed in (2,0) (y,x)
    std::vector<Grid> gridsToWin;
    grid = {{"X","", ""},  
            {"" ,"X", ""} ,
            {"" ,"O", "O"} };
    gridsToWin.push_back(grid);
    grid = {{"X", "", "O"},  
            {"" ,"O", "X"} ,
            {"" ,"",  ""} };
    gridsToWin.push_back(grid);
    grid = {{"O","", ""},  
            {"O" ,"", "X"} ,
            {"" ,"X", ""} };
    gridsToWin.push_back(grid);
    

    for (Grid g : gridsToWin)
    {
        State state(g, ai_mark, 0);
        State new_state = ai.move(state);
        Move ai_move = new_state.getCrucialMove();
        BOOST_CHECK ( ai_move == std::make_pair(2,0));
    }


}
