#include <boost/python/suite/indexing/vector_indexing_suite.hpp> 
#include <iostream>
#include <boost/python.hpp>

using namespace boost::python;

bool draw(object grid)
{
    return true;
}

void print_list(std::vector<std::string> list)
{
    std::vector<std::string>::iterator it;
    it = list.begin();
    for ( ; it != list.end(); it++)
        std::cout << *it << std::endl;
}

BOOST_PYTHON_MODULE(game_status)
{
    def("draw", draw, args("grid"), "draw's docstring");

    def("print_list", print_list, args("list"));
    
    // vector of strings
    class_<std::vector<std::string> >("StringVec")
        .def(vector_indexing_suite<std::vector<std::string> >())
    ;
}
