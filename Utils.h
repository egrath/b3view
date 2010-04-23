#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <irrlicht.h>
#include "Debug.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace std;

class Utility
{
public:
    static void dumpVectorToConsole( const vector3df &vector );
    static void dumpMeshInfoToConsole( IAnimatedMeshSceneNode *node );
};

#endif // UTILS_H
