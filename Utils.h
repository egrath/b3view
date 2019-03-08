#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <irrlicht/irrlicht.h>
#include "Debug.h"

class Utility
{
public:
    static void dumpVectorToConsole( const irr::core::vector3df &vector );
    static void dumpMeshInfoToConsole( irr::scene::IAnimatedMeshSceneNode *node );
    static std::wstring parentOfPath(const std::wstring &path);
};

#endif // UTILS_H
