#include <unordered_map>

namespace DisplaySettings
{
    enum Mode{
        SD,
        HD,
        FullHD
    } CurrentMode = SD;

    struct Dimensions
    {
        int width;
        int height;
    };

    const std::unordered_map<Mode,Dimensions> modes = {
        { SD,       {800, 600}},
        { HD,       {1280, 720}},
        { FullHD,   {1920, 1080}}
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