#include "ai.hpp"

State::State(int utility)
{
    this->utility = utility;
}

State::State(Grid grid, std::string player_to_move, PMove last_move, int utility) 
{
    this->grid = grid;
    this->player_to_move = player_to_move;
    this->last_move = last_move;
    this->utility = utility;
}


Ai::Ai(PSettings settings, int max_depth)
{
    this->settings = settings;
    this->max_depth = max_depth;
    this->status = new Status(settings);
}

State Ai::move(State state)
{
    int infinity = std::numeric_limits<int>::max();
    State alpha(-infinity);
    State beta(+infinity);
    return negamax(state, alpha, beta);
}

State Ai::negamax(State state, State alpha, State beta, int depth)
{
    Grid grid = state.grid;
    std::string player = state.player_to_move;

    if (terminalState(state) || depth > max_depth)
    {
        int evaluation = evaluate(grid, player);
        State new_state = State(grid, opponent(player), state.last_move, evaluation);
        return new_state; 
    }

    int infinity = std::numeric_limits<int>::max();
    State maximum(-infinity);

    for (Move move: moves(grid))
    {
        // deepcopy
        Grid grid_copy = grid;
        grid_copy = makeMove(grid_copy, move, player);

        PMove new_state_move;
        if (state.last_move == nullptr)
            new_state_move = boost::make_shared<Move>(move);
        else
            new_state_move = state.last_move;

        State new_state = State(grid_copy, opponent(player), new_state_move, 0);

        State new_alpha = alpha;
        new_alpha.utility = (- alpha.utility);

        State new_beta = beta;
        new_beta.utility = (- beta.utility);

        State x = negamax(new_state, new_beta, new_alpha, depth+1);
        x.utility = (- x.utility);

        if (x.utility > maximum.utility)
            maximum = x;

        if (x.utility > alpha.utility)
            alpha = x;

        if (alpha.utility >= beta.utility)
            return alpha;
    }
    return maximum;
}

bool Ai::terminalState(State state)
{
    std::string player = state.player_to_move;
    if (status->winner(state.grid, player) ||
        status->winner(state.grid, opponent(player)) ||
        status->draw(state.grid))
        return true;
    return false;
}

int Ai::evaluate(Grid grid, std::string player)
{
    bool isHumanWon = status->winner(grid, settings->getPlayerMark());
    bool isAiWon = status->winner(grid, settings->getAiMark());

    if (isHumanWon)
    {
        if (player == settings->getPlayerMark())
            return 1;
        else 
            return -1;
    }

    if (isAiWon)
    {
        if (player == settings->getAiMark())
            return 1;
        else
            return -1;
    }

    return 0;
    
}

std::vector<Move> Ai::moves(Grid grid)
{
    int width = settings->getGridWidth();
    int height = settings->getGridHeight();
    std::vector<Move> moves;
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            if (grid[y][x].empty())
                moves.push_back( std::make_pair(y, x) );
        }
    }
    return moves;
}

Grid Ai::makeMove(Grid grid, Move move, std::string player)
{
    int y = move.first;
    int x = move.second;
    grid[y][x] = player;
    return grid;

}

std::string Ai::opponent(std::string player)
{
    if (player == settings->getPlayerMark())
        return settings->getAiMark();
    else
        return settings->getPlayerMark();
}

