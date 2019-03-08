#include "Utils.h"
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


