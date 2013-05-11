#include <boost/python/suite/indexing/vector_indexing_suite.hpp> 
#include <iostream>
#include <boost/python.hpp>

#include "settings.hpp"
#include "status.hpp"

using namespace boost::python;
using namespace std;

//bool draw(vector <vector<string> > matrix)
//{
//    vector<vector<string> >::iterator row;
//    vector<string>::iterator column;
//    for (row = matrix.begin(); row != matrix.end(); row++)
//    {
//        for (column = (*row).begin(); column != (*row).end(); column++)
//        {
//            if ((*column).empty())
//                return false;
//        }
//    }
//    return true;
//}

void print_list(vector<string> list)
{
    vector<string>::iterator it;
    it = list.begin();
    for ( ; it != list.end(); it++)
        cout << *it << endl;
}


void print_matrix(vector <vector<string> > matrix)
{
    vector <vector<string> >::iterator row;
    vector<string>::iterator column;
    for (row = matrix.begin(); row != matrix.end(); row++)
    {
        for (column = (*row).begin(); column != (*row).end(); column++)
        {
            cout << *column << " ";
        }
        cout << endl;
    }
}

BOOST_PYTHON_MODULE(game_status)
{
//    def("draw", draw, args("grid"), "draw's docstring");
    def("print_list", print_list, args("list"));
    def("print_matrix", print_matrix, args("matrix"));
    
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
        .def_readwrite("first", &std::pair<int, int>::first);
        .def_readwrite("second", &std::pair<int, int>::second);

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
}
