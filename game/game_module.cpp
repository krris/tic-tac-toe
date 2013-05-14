#include <boost/python/suite/indexing/vector_indexing_suite.hpp> 
#include <iostream>
#include <boost/python.hpp>

#include "settings.hpp"
#include "status.hpp"
#include "ai.hpp"

using namespace boost::python;
using namespace std;

BOOST_PYTHON_MODULE(game)
{
    // vector of strings
    class_<vector<string> >("StringVec")
        .def(vector_indexing_suite<vector<string> >())
    ;

    // vector of vector of strings
    class_<vector <vector<string> > >("StringMatrix")
        .def(vector_indexing_suite<vector <vector<string> > >())
    ;

    // pair of integers
    class_<std::pair<int, int> >("IntPair")
        .def_readwrite("first", &std::pair<int, int>::first)
        .def_readwrite("second", &std::pair<int, int>::second)
    ;

    class_<Settings, boost::shared_ptr<Settings>, boost::noncopyable>
        ("Settings", no_init) 
        .def("get_instance", &Settings::getInstance )
        .staticmethod("get_instance")
        .def("initialize", &Settings::initialize, args("grid_width", "grid_height",
             "marks_to_win", "player_mark", "ai_mark"), "Settings docstring")
    ;

    // Member function pointers variables for handling overloade functions
    bool (Status::*winner_ver1)(Grid, std::string) = &Status::winner;
    bool (Status::*winner_ver2)(Grid, Move, std::string) = &Status::winner;

    class_<Status>("Status", init<boost::shared_ptr<Settings> >())
        .def("draw", &Status::draw, args("grid"), "status::draw Docstring")
        .def("winner", winner_ver1)
        .def("winner", winner_ver2) 
    ;

    class_<State>("State")
        .def(init<>())
        .def(init<int>())
        .def(init<Grid, std::string, int>())
        .def(init<Grid, std::string, PMove, int>())
        .def("get_crucial_move", &State::getCrucialMove)
    ;

    class_<Ai>("Ai", init<boost::shared_ptr<Settings>, int>())
        .def("move", &Ai::move, args("state"), "Doscstring")
    ;
        
}
