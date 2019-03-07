#include "Utils.h"

void Utility::dumpVectorToConsole( const vector3df &vector )
{
    debug() << "X: " << vector.X << " Y: " << vector.Y << " Z: " << vector.Z  << endl;
}

void Utility::dumpMeshInfoToConsole( IAnimatedMeshSceneNode *node )
{
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


