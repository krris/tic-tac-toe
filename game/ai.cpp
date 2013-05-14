#include "ai.hpp"

State::State(int utility)
{
    this->utility = utility;
}

State::State(Grid grid, std::string player_to_move, int utility)
{
    this->grid = grid;
    this->player_to_move = player_to_move;
    this->utility = utility;
}


State::State(Grid grid, std::string player_to_move, PMove crucial_move, int utility) 
{
    this->grid = grid;
    this->player_to_move = player_to_move;
    this->crucial_move = crucial_move;
    this->utility = utility;
}

Move State::getCrucialMove() const
{ 
    return *crucial_move; 
}

Ai::Ai(PSettings settings, int max_depth)
{
    this->settings = settings;
    this->max_depth = max_depth;
    this->status = new Status(settings);
}

State Ai::move(const State& state) 
{
    int infinity = std::numeric_limits<int>::max();
    State alpha(-infinity);
    State beta(+infinity);
    return negamax(state, alpha, beta);
}

State Ai::negamax(const State& state, State alpha, State beta, int depth)
{
    Grid grid = state.grid;
    std::string player = state.player_to_move;

    if (terminalState(state) || depth > max_depth)
    {
        int evaluation = evaluate(grid, player);
        State new_state = State(grid, opponent(player), state.crucial_move, evaluation);
        return new_state; 
    }

    int infinity = std::numeric_limits<int>::max();
    State maximum(-infinity);

    for (Move move: moves(grid))
    {
        Grid grid_copy = makeMove(grid, move, player);

        PMove new_state_move;
        if (state.crucial_move == nullptr)
            new_state_move = boost::make_shared<Move>(move);
        else
            new_state_move = state.crucial_move;

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

bool Ai::terminalState(const State& state) const
{
    std::string player = state.player_to_move;
    if (status->winner(state.grid, player) ||
        status->winner(state.grid, opponent(player)) ||
        status->draw(state.grid))
        return true;
    return false;
}

int Ai::evaluate(const Grid& grid, const std::string& player) const
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

std::vector<Move> Ai::moves(const Grid& grid) const
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

Grid Ai::makeMove(const Grid& grid, const Move& move, const std::string& player) const
{
    // deepcopy
    Grid grid_copy(grid);
    int y = move.first;
    int x = move.second;
    grid_copy[y][x] = player;
    return grid_copy;

}

std::string Ai::opponent(const std::string& player) const
{
    if (player == settings->getPlayerMark())
        return settings->getAiMark();
    else
        return settings->getPlayerMark();
}

