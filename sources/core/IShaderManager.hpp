#pragma once

#include <memory>
#include <string>

namespace core
{
    class IShader;

    class IShaderManager
    {
    public:
        virtual std::weak_ptr<IShader> LoadVertexShader(const std::string& filename) = 0;
        virtual std::weak_ptr<IShader> LoadFragmentShader(const std::string& filename) = 0;

        virtual ~IShaderManager() = default;
    };

    std::unique_ptr<IShaderManager> CreateShaderManager();
}