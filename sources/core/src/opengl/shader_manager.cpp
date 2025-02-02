#include "shader_manager.hpp"
#include "shader.hpp"

#include "utils/filesystem/app_utils.hpp"

namespace core::opengl
{
    template<typename TShaderType>
    std::weak_ptr<IShader> ShaderManager::LoadShader(const std::string& filename)
    {
        auto it = m_shaders.find(filename);
        if (it != m_shaders.end())
            return it->second;

        const auto pair = m_shaders.emplace(filename, std::make_shared<IShader>(TShaderType(filename)) );

        return pair.first->second;
    }

    std::weak_ptr<IShader> ShaderManager::LoadVertexShader(const std::string& filename)
    {
        return LoadShader<VertexShader>(filename);
    }

    std::weak_ptr<IShader> ShaderManager::LoadFragmentShader(const std::string& filename)
    {
        return LoadShader<FragmentShader>(filename);
    }
}

namespace core
{
    std::unique_ptr<IShaderManager> CreateShaderManager()
    {
        return std::make_unique<opengl::ShaderManager>();
    }
}