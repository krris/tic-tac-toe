#include "ai.hpp"

State::State(Grid grid, std::string player_to_move, Move last_move, int utility) 
{

}

Ai::Ai(PSettings settings, int max_depth)
{
    this->settings = settings;
    this->max_depth = max_depth;
    this->status = new Status(settings);
}

void Ai::move(State state)
{

}

