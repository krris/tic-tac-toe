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
    for (Row row: winning_combos)
    {
        int counter = 0;
        for (Move move: row)
        {
            int y = move.first;
            int x = move.second;
            if (grid[y][x] == player)
               counter++;
            if (counter == settings->getMarksToWin())
               return true; 
        } 
    }
    return false;
}

bool Status::winner(Grid grid, Move move, std::string player) 
{
    if (kInRow(grid, move, player, 0, 1) ||
        kInRow(grid, move, player, 1, 0) ||
        kInRow(grid, move, player, 1, -1) ||
        kInRow(grid, move, player, 1, 1) )
        return true;
    else
        return false;
}


bool Status::kInRow(Grid grid, Move move, std::string player, int delta_x, int delta_y)
{
    int x = move.first;
    int y = move.second;

    // n is a number of moves in row
    int n = 0;
    while( true )  
    {
        if (outOfGridRange(x, y))
            break;
        if (grid[x][y] == player)
        {
            n++;
            x += delta_x;
            y += delta_y;
        } 
        else
            break;
    } 
    x = move.first;
    y = move.second;
    while( true )  
    {
        if (outOfGridRange(x, y))
            break;
        if (grid[x][y] == player)
        {
            n++;
            x -= delta_x;
            y -= delta_y;
        } 
        else
            break;
    } 
    n -= 1; // becouse we counted move itself twice
    return (n >= settings->getMarksToWin());

}

bool Status::outOfGridRange(int x, int y)
{
    if (x < 0 || y < 0)
        return true;
    if (x >= settings->getGridWidth() || y >= settings->getGridHeight())
        return true;
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

    for (int x = width - 1; x > width - marks_to_win + 1; --x)
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

