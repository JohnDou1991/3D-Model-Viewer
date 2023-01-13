#pragma once

#include "objects/mesh.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace object
{
    class Model 
    {

    public:
        Model( const std::string& path )
        {
            loadModel( path );
        }
        void Draw(GLuint shaderProgram);

    private:
        // model data
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel( const std::string& path );
        void processNode( aiNode *node, const aiScene *scene );
        Mesh processMesh( aiMesh *mesh, const aiScene *scene );
        std::vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, std::string typeName );
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    };
}