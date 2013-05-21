#ifndef AI_HPP
#define AI_HPP

#include <limits>

#include "forward_declarations.h"
#include "settings.hpp"
#include "status.hpp"

/**
 * Holds information about a state of the game.
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

    Move getCrucialMove() const;

    Grid grid;
    std::string player_to_move;
    PMove crucial_move;
    int utility;
    
};

/**
 * Implements an artificial intelligence for a computer.
 */
class Ai{
public:
    Ai(int max_depth);
    /**
     * Make a move on the base of passed state.
     * @param state
     */
    State move(const State& state);

private:
    /**
     * Make a move using the negamax alorithm.
     * @state
     * @alpha State which holds the best result.
     * @beta State which holds the worst result.
     */
    State negamax(const State& state, State alpha, State beta, int depth=0);

    /**
     * Check if passed state is a terminal state (someone won or 
     * there's no any placy to make a move).
     */
    bool terminalState(const State& state) const;

    /**
     * Calculate a desirability of current situation on a grid.
     * @param grid
     * @param player for which an evaluation will be made
     */
    int evaluate(const Grid& grid, const std::string& player) const;

    /**
     * Get all the possible moves.
     */
    std::vector<Move> moves(const Grid& grid) const;

    Grid makeMove(const Grid& grid, const Move& move, const std::string& player) const;

    /**
     * Get the opponent of a passed player.
     */
    std::string opponent(const std::string& player) const;


    PSettings settings;

    /* Maximal depth of the negamax algorithm  */
    int max_depth;
    Status* status;

};

#endif
