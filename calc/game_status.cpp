#include <boost/python/suite/indexing/vector_indexing_suite.hpp> 
#include <iostream>
#include <boost/python.hpp>

using namespace boost::python;

bool draw(object grid)
{

    return true;
}

BOOST_PYTHON_MODULE(game_status)
{
    def("draw", draw, args("grid"), "draw's docstring");
    
    // vector of strings
    class_<std::vector<std::string> >("StringVec")
        .def(vector_indexing_suite<std::vector<std::string> >())
    ;
}
