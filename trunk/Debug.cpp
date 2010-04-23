#include "Debug.h"

ostream & debug()
{
    std::flush( cout );
    return cout;
}
