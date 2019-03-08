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
    static std::wstring basename(const std::wstring &path);
    static std::wstring withoutExtension(const std::wstring &path);
    static std::wstring delimiter(const std::wstring &path);
    static bool isFile(const std::string &name);
    static bool isFile(const std::wstring &name);
    static std::string toString(const std::wstring &name);
};

#endif // UTILS_H
