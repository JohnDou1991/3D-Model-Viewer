#pragma once

#include "IShaderManager.hpp"

#include <map>

namespace core::opengl
{
    class ShaderManager final : public IShaderManager
    {
        std::map<std::string, std::shared_ptr<IShader>> m_shaders;

        template<typename TShaderType>
        std::weak_ptr<IShader> LoadShader(const std::string& filename);

    public:
        std::weak_ptr<IShader> LoadVertexShader(const std::string& filename) override;
        std::weak_ptr<IShader> LoadFragmentShader(const std::string& filename) override;

        ~ShaderManager() = default;
    };
};