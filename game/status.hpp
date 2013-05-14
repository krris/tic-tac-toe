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
    /**
     * Check if there is a draw.
     */
    bool draw(const Grid& grid) const;
    /**
     * Check if passed player is a winner.
     */
    bool winner(const Grid& grid, const std::string& player) const;
    /**
     * Check if passed player is a winner. All the calculations are based on last player move.
     */
    bool winner(const Grid& grid, const Move& move, const std::string& player) const;
private:
    /**
     * Generate all possible winning situation in columns.
     */
    std::vector<Row> getWinningColumns();

    /**
     * Generate all possible winning situation in rows.
     */
    std::vector<Row> getWinningRows();

    /**
     * Generate all possible winning situation in diagonal.
     */
    std::vector<Row> getWinningDiagonals();

    /**
     * Check if there are k marks (= marks to win) in a row.
     * @return true if player is a winner 
     */
    bool kInRow(const Grid& grid, const Move& move, const std::string& player,
                int delta_x, int delta_y) const;
    bool outOfGridRange(int x, int y) const;

    PSettings settings;

    /** All possible winnging combinations.*/
    std::vector<Row> winning_combos;
};

#endif
