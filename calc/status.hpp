#ifndef STATUS_HPP
#define STATUS_HPP

#include <string>
#include <boost/smart_ptr.hpp>
#include <string>

#include "settings.hpp"

typedef std::vector<std::vector<std::string> > Grid;

class Status{
public:
    Status(PSettings settings);
    bool draw(Grid grid);
private:
    PSettings settings;
};

#endif
