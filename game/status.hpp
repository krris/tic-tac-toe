#ifndef STATUS_HPP
#define STATUS_HPP

#include <string>
#include <boost/smart_ptr.hpp>
#include <string>

#include "settings.hpp"

typedef std::vector<std::vector<std::string> > Grid;
typedef std::pair<int, int> Move;
typedef std::vector<Move> Row;

class Status{
public:
    Status(PSettings settings);
    bool draw(const Grid& grid) const;
    bool winner(const Grid& grid, const std::string& player) const;
    bool winner(const Grid& grid, const Move& move, const std::string& player) const;
private:
    std::vector<Row> getWinningColumns();
    std::vector<Row> getWinningRows();
    std::vector<Row> getWinningDiagonals();

    bool kInRow(const Grid& grid, const Move& move, const std::string& player,
                int delta_x, int delta_y) const;
    bool outOfGridRange(int x, int y) const;

    PSettings settings;
    std::vector<Row> winning_combos;
};

#endif
