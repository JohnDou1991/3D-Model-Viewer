#include "cube.hpp"

#include "IShaderManager.hpp"
#include "ITextureManager.hpp"

namespace assets
{
    Cube::Cube(const std::unique_ptr<core::IShaderManager>& shaderManager
              ,const std::unique_ptr<core::ITextureManager>& textureManager)
    {
        m_shaders.emplace_back( shaderManager->LoadVertexShader("light.vs") );
        m_shaders.emplace_back( shaderManager->LoadFragmentShader("lightObject.fs") );

        m_textures.emplace_back( textureManager->LoadTexture("container2.png") );
        m_textures.emplace_back( textureManager->LoadTexture("container2_specular.png") );
    }

    void Cube::Draw()
    {
        for ( size_t i = 0; i < m_textures.size(); ++i ) 
            m_textures[i].lock()->Bind(i);
    }

    Cube::~Cube()
    {

    }
}