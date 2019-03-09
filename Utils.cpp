#include "Utils.h"
#include <string>
#include <iostream>
#include <clocale>
#include <locale>
#include <vector>
#include <cmath>
#include <cwctype>  // #include <cwtype>
#include <algorithm>

#include "Debug.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace std;


void Utility::dumpVectorToConsole( const vector3df &vector )
{
    debug() << "X: " << vector.X << " Y: " << vector.Y << " Z: " << vector.Z  << endl;
}

void Utility::dumpMeshInfoToConsole( IAnimatedMeshSceneNode *node )
{
    if (node == nullptr) {
        debug() << "[MESH]: # node: nullptr" << endl;
        return;
    }
    if (node->getMesh() == nullptr) {
        debug() << "[MESH]: # node->getMesh(): nullptr" << endl;
        return;
    }
    // Dump some information about the mesh to the console
    IAnimatedMesh *mesh = node->getMesh();

    debug() << "[MESH]: # of frames            : " << mesh->getFrameCount() << endl;
    debug() << "[MESH]: # of materials         : " << node->getMaterialCount() << endl;
    for( int matIndex = 0; matIndex < node->getMaterialCount(); matIndex ++ )
    {
        debug() << "[MESH]:   Material # " << matIndex << endl;
        const SMaterial &material = node->getMaterial( matIndex );
        debug() << "[MESH]:      Diffuse Color       : A" << material.DiffuseColor.getAlpha() << " R" << material.DiffuseColor.getRed() << " G" << material.DiffuseColor.getGreen() << " B" << material.DiffuseColor.getBlue() << endl;
        debug() << "[MESH]:      Specular Color      : A" << material.SpecularColor.getAlpha() << " R" << material.SpecularColor.getRed() << " G" << material.SpecularColor.getGreen() << " B" << material.SpecularColor.getBlue() << endl;
        debug() << "[MESH]:      Specular Shininess  : " << material.Shininess << endl;

        // check for # textures
        int textures = 0;
        for( int ti = 0; ti < MATERIAL_MAX_TEXTURES; ti ++ )
            if( material.getTexture( ti ) != nullptr ) textures ++;
        debug() << "[MESH]:      # of textures       : " << textures << endl;
    }
}

std::wstring Utility::parentOfPath(const wstring &path)
{
    std::wstring ret = L".";
    if (path == L".") {
        ret = L"..";
    }
    else {
        std::wstring::size_type lastSlashPos = path.find_last_of(L"/");
        if (lastSlashPos == std::wstring::npos) {
            std::wstring::size_type lastSlashPos = path.find_last_of(L"\\");
        }
        if (lastSlashPos != std::wstring::npos) {
            ret = path.substr(0, lastSlashPos);
        }
    }
    return ret;
}

wstring Utility::basename(const wstring &path)
{
    std::wstring ret = path;
    std::wstring::size_type lastSlashPos = path.find_last_of(L"/");
    if (lastSlashPos == std::wstring::npos) {
        std::wstring::size_type lastSlashPos = path.find_last_of(L"\\");
    }
    if (lastSlashPos != std::wstring::npos) {
        ret = path.substr(lastSlashPos+1);
    }
    return ret;
}

wstring Utility::withoutExtension(const wstring &path)
{
    std::wstring ret = path;
    std::wstring::size_type lastDotPos = path.find_last_of(L".");
    if (lastDotPos != std::wstring::npos) {
        std::wstring::size_type lastSlashPos = path.find_last_of(L"/");
        if (lastSlashPos == std::wstring::npos) {
            std::wstring::size_type lastSlashPos = path.find_last_of(L"\\");
        }
        if (lastSlashPos != std::wstring::npos) {
            if (lastDotPos > lastSlashPos) ret = path.substr(0, lastDotPos);
        }
        else ret = path.substr(0, lastDotPos);
    }
    return ret;
}

wstring Utility::extensionOf(const wstring &path)
{
    std::wstring ret = L"";
    std::wstring::size_type lastDotPos = path.find_last_of(L".");
    if (lastDotPos != std::wstring::npos) {
        std::wstring::size_type lastSlashPos = path.find_last_of(L"/");
        if (lastSlashPos == std::wstring::npos) {
            std::wstring::size_type lastSlashPos = path.find_last_of(L"\\");
        }
        if (lastSlashPos != std::wstring::npos) {
            if (lastDotPos > lastSlashPos) ret = path.substr(lastDotPos + 1);
        }
        else ret = path.substr(lastDotPos + 1);
    }
    return ret;
}

wstring Utility::delimiter(const wstring &path)
{
    std::wstring ret = L"/";
    std::wstring::size_type lastSlashPos = path.find_last_of(L"/");
    if (lastSlashPos == std::wstring::npos) {
        // ret = "/";
    }
    else {
        std::wstring::size_type lastSlashPos = path.find_last_of(L"\\");
        if (lastSlashPos != std::wstring::npos) {
            ret = L"\\";
        }
    }
    return ret;
}

bool Utility::isFile(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string Utility::toString(const std::wstring& ws) {
    std::string ret;
    // convert to w_string using locale: see Phillipp on <https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string>
    std::setlocale(LC_ALL, "");
    const std::locale locale("");
    typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
    const converter_type& converter = std::use_facet<converter_type>(locale);
    std::vector<char> to(ws.length() * converter.max_length());
    std::mbstate_t state;
    const wchar_t* from_next;
    char* to_next;
    const converter_type::result result = converter.out(state, ws.data(), ws.data() + ws.length(), from_next, &to[0], &to[0] + to.size(), to_next);
    if (result == converter_type::ok or result == converter_type::noconv) {
        const std::string s(&to[0], to_next);
        //std::cout <<"std::string =     "<<s<<std::endl;
        ret = s;
    }
    return ret;
}

std::string Utility::toLower(const std::string &s)
{
    std::string ret = s;
    std::transform( ret.begin(), ret.end(), ret.begin(), ::tolower);
    return ret;
}

wstring Utility::toLower(const wstring &s)
{
    wstring ret = s;
    std::transform( ret.begin(), ret.end(), ret.begin(), towlower);
    return ret;
}

bool Utility::isFile(const std::wstring& name) {
    std::string name_s = toString(name);
    if (FILE *file = fopen(name_s.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}


