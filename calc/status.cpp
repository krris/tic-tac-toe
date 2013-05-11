#include "status.hpp"

Status::Status(PSettings settings)
{
    this->settings = settings;
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
