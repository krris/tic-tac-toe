#include "status.hpp"

Status::Status(PSettings settings)
{
    this->settings = settings;
    std::vector<Row> winning_columns = getWinningColumns();
    std::vector<Row> winning_rows = getWinningRows();
    std::vector<Row> winning_diagonals = getWinningDiagonals();

    this->winning_combos.insert(winning_combos.end(), 
                                winning_rows.begin(), winning_rows.end());

    this->winning_combos.insert(winning_combos.end(), 
                                winning_columns.begin(), winning_columns.end());

    this->winning_combos.insert(winning_combos.end(), 
                                winning_diagonals.begin(), winning_diagonals.end());
}

bool Status::draw(Grid grid)
{
    using namespace std;
    Grid::iterator row;
    vector<string>::iterator column;
    for (row = grid.begin(); row != grid.end(); row++)
    {
        for (column = (*row).begin(); column != (*row).end(); column++)
        {
            if ((*column).empty())
                return false;
        }
    }
    return true;
}

bool Status::winner(Grid grid, std::string player)
{
    return false;
}

bool Status::winner(Grid grid, Move move, std::string player) 
{
    return false;
}

std::vector<Row> Status::getWinningColumns()
{
    int height = settings->getGridHeight();
    int width = settings->getGridWidth();
    int marks_to_win = settings->getMarksToWin();
    std::vector<Row> columns;

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < (height - marks_to_win + 1); ++y)
        {
            Row column;
            for (int i = 0; i < marks_to_win; ++i)
            {
                column.push_back( std::make_pair(y + i, x));
            }
            columns.push_back(column);
        }
    }
    return columns;
}

std::vector<Row> Status::getWinningRows() 
{
    int height = settings->getGridHeight();
    int width = settings->getGridWidth();
    int marks_to_win = settings->getMarksToWin();
    std::vector<Row> rows;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < (width - marks_to_win + 1); ++x)
        {
            Row row;
            for (int i = 0; i < marks_to_win; ++i)
            {
                row.push_back( std::make_pair(y, x + i));
            }
            rows.push_back(row);
        }
    }
    return rows;

}

std::vector<Row> Status::getWinningDiagonals() 
{
    int height = settings->getGridHeight();
    int width = settings->getGridWidth();
    int marks_to_win = settings->getMarksToWin();
    std::vector<Row> diagonals;

    for (int x = 0; x < width - marks_to_win + 1; ++x)
    {
        for (int y = 0; y < (height - marks_to_win + 1); ++y)
        {
            Row diagonal;
            for (int i = 0; i < marks_to_win; ++i)
            {
                diagonal.push_back( std::make_pair(y + i, x + i));
            }
            diagonals.push_back(diagonal);
        }
    }

    for (int x = width - 1; x > width - marks_to_win; --x)
    {
        for (int y = 0; y < (height - marks_to_win + 1); ++y)
        {
            Row diagonal;
            for (int i = 0; i < marks_to_win; ++i)
            {
                diagonal.push_back( std::make_pair(y + i, x - i));
            }
            diagonals.push_back(diagonal);
        }
    }

    return diagonals;
}

