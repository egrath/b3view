#include "Debug.h"

using std::cout;
using std::endl;
using std::ostream;
using std::wcout;
using std::wcerr;

ostream & debug()
{
    std::flush( cout );
    return cout;
}
