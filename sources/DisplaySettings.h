#pragma once

#include <unordered_map>

namespace DisplaySettings
{
    enum class Mode{
        SD,
        HD,
        FHD,
        UHD
    };

    struct Dimensions
    {
        int width;
        int height;
    };

    const std::unordered_map<Mode,Dimensions> modes = {
        { Mode::SD,   {800, 600}},
        { Mode::HD,   {1280, 720}},
        { Mode::FHD,  {1920, 1080}},
        { Mode::UHD,  {2560, 1440}}
    };

    class Window
    {
        Dimensions m_dimensions;
    public:
        explicit Window( Mode mode ) : m_dimensions(modes.at(mode))
        {

        }

        int height() const
        {
            return m_dimensions.height;
        }

        int width() const
        {
            return m_dimensions.width;
        }
    };
}