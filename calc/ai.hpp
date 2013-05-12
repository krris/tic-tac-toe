#ifndef AI_HPP
#define AI_HPP

#include "settings.hpp"
#include "status.hpp"

struct State{
    State() {}
    State(Grid grid, std::string player_to_move,
          Move last_move, int utility);

    Grid grid;
    std::string player_to_move;
    Move last_move;
    int utility;
    
};

class Ai{
public:
    Ai(PSettings settings, int max_depth);
    void move(State state);
private:
    State negamax(State state);
    bool terminalState(State state);
    int evaluate(Grid grid, std::string player);
    std::vector<Move> moves(Grid grid);
    Grid makeMove(Grid grid, Move move, std::string player);
    std::string opponent(std::string player);


    PSettings settings;
    int max_depth;
    Status* status;

};

#endif
