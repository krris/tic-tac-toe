#ifndef AI_HPP
#define AI_HPP

#include <limits>
#include <boost/smart_ptr.hpp>

#include "settings.hpp"
#include "status.hpp"

typedef boost::shared_ptr<Move> PMove;

/**
 * Hold information about a state of the game.
 */
struct State{

    State() {}
    /**
     * @param utility Calculated utility of the current state.
     */
    State(int utility);

    /**
     * @param grid A grid (board) of the game.
     * @param player_to_move Next player, which will make a move.
     * @param utility Calculated utility of the current state.
     */
    State(Grid grid, std::string player_to_move, int utility);
    State(Grid grid, std::string player_to_move,
          PMove crucial_move, int utility);

    Move getCrucialMove();

    Grid grid;
    std::string player_to_move;
    PMove crucial_move;
    int utility;
    
};

class Ai{
public:
    Ai(PSettings settings, int max_depth);
    State move(State state);

private:
    State negamax(State state, State alpha, State beta, int depth=0);
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
