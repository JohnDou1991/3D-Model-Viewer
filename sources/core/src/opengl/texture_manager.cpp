#include "texture_manager.hpp"
#include "texture.hpp"

#include "utils/filesystem/app_utils.hpp"

namespace core::opengl
{
    std::weak_ptr<ITexture> TextureManager::LoadTexture(const std::string& filename)
    {
        auto it = m_textures.find(filename);
        if (it != m_textures.end())
            return it->second;
        
        const auto path = utils::getCurrentDir() + "/resources/textures/" + filename;
        auto pair = m_textures.emplace(filename, std::make_shared<Texture>(path) );

        return pair.first->second;
    }
};

namespace core
{
    std::unique_ptr<ITextureManager> CreateTextureManager()
    {
        return std::make_unique<opengl::TextureManager>();
    }
}