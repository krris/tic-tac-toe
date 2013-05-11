#include <boost/test/minimal.hpp>
#include <log4cxx/basicconfigurator.h>

using namespace log4cxx;
LoggerPtr logger(Logger::getRootLogger());

int test_main( int argc, char* argv[] )
{
    BasicConfigurator::configure();
    LOG4CXX_INFO(logger, "Hello");
    return 0;
}
