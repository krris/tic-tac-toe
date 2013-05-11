#ifndef STATUS_HPP
#define STATUS_HPP

#include <string>
#include <boost/smart_ptr.hpp>
#include <string>
#include <stdexcept>

#include "settings.hpp"

typedef std::vector<std::vector<std::string> > Grid;
typedef std::pair<int, int> Move;
typedef std::vector<Move> Row;

class Status{
public:
    Status(PSettings settings);
    bool draw(Grid grid);
    bool winner(Grid grid, std::string player);
    bool winner(Grid grid, Move move, std::string player);
private:
    std::vector<Row> getWinningColumns();
    std::vector<Row> getWinningRows();
    std::vector<Row> getWinningDiagonals();

    bool kInRow(Grid grid, Move move, std::string player,
                int delta_x, int delta_y);
    bool exists(Grid grid, int index);
    bool exists(std::vector<std::string> row, int index);

    PSettings settings;
    std::vector<Row> winning_combos;
};

#endif
