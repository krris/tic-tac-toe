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

    Move getCrucialMove() const;

    Grid grid;
    std::string player_to_move;
    PMove crucial_move;
    int utility;
    
};

class Ai{
public:
    Ai(PSettings settings, int max_depth);
    State move(const State& state);

private:
    State negamax(const State& state, State alpha, State beta, int depth=0);
    bool terminalState(const State& state) const;
    int evaluate(const Grid& grid, const std::string& player) const;
    std::vector<Move> moves(const Grid& grid) const;
    Grid makeMove(const Grid& grid, const Move& move, const std::string& player) const;
    std::string opponent(const std::string& player) const;


    PSettings settings;
    int max_depth;
    Status* status;

};

#endif
