#ifndef UTILS_H
#define UTILS_H

#include <string>

#include <irrlicht/irrlicht.h>

class Utility
{
public:
    static void dumpVectorToConsole( const irr::core::vector3df &vector );
    static void dumpMeshInfoToConsole( irr::scene::IAnimatedMeshSceneNode *node );
    static std::wstring parentOfPath(const std::wstring &path);
    static std::wstring basename(const std::wstring &path);
    static std::wstring withoutExtension(const std::wstring &path);
    static std::wstring extensionOf(const std::wstring &path);
    static std::wstring delimiter(const std::wstring &path);
    static bool isFile(const std::string &name);
    static bool isFile(const std::wstring &name);
    static std::string toString(const std::wstring &name);
    static std::string toLower(const std::string &s);
    static std::wstring toLower(const std::wstring &s);
    // compiler doesn't like template function when class is not a template--instantiate immediately
    // see http://processors.wiki.ti.com/index.php/C%2B%2B_Template_Instantiation_Issues
    template <typename T>
    static bool equalsApprox(T f1, T f2) {
        return abs(f2-f1) < .00000001;  // TODO: kEpsilon? (see also <https://en.wikipedia.org/wiki/Machine_epsilon#How_to_determine_machine_epsilon>)
    }
};

#endif // UTILS_H
