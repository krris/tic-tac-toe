#ifndef FORWARD_DECLARATIONS_H
#define FORWARD_DECLARATIONS_H

#include <boost/smart_ptr.hpp>

typedef std::vector<std::vector<std::string> > Grid;
typedef std::pair<int, int> Move;
typedef std::vector<Move> Row;


typedef boost::shared_ptr<Move> PMove;

class Settings;
typedef boost::shared_ptr<Settings> PSettings;

#endif 
