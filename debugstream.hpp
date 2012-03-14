
#ifndef DEBUG_STREAM_H_included
#define DEBUG_STREAM_H_included

#include <iosfwd>

namespace debug {

    namespace detail {

        template <typename T>
        struct Streamer
        {
            const T& value_;
            bool verbose_;

            Streamer(const T& value, bool verbose)
                : value_(value), verbose_(verbose) {}
        };

    }

    template <typename T>
    detail::Streamer<T> brief(const T& value)
    {
        return detail::Streamer<T>(value, false);
    }

    template <typename T>
    detail::Streamer<T> verbose(const T& value)
    {
        return detail::Streamer<T>(value, true);
    }

}

template <typename T>
std::ostream& operator<<(std::ostream& o, const debug::detail::Streamer<T>& s)
{
    print_debug_details(o, s.value_, s.verbose_);
    return o;
}

#endif  // DEBUGSTREAM_H_included

