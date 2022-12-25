
namespace std
{
    template<typename T>
    T clamp(T from, T to, T value)
    {
        if ( value < from )
            return from;
        
        if ( value > to )
            return to;

        return value;
    }
}