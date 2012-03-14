
#ifndef DEBUG_STREAM_H_included
#define DEBUG_STREAM_H_included

#include <iosfwd>

// A simple mechanism for writing debug info to an ostream.  Just
// implement print_debug_details() for whatever type you are interested
// in, optionally observing the verbose flag if distinct brief and
// verbose outputs are desired.
//
// An example implementation for int's:
//
//   #include "debugstream.hpp"
//
//   #include <iostream>
//
//   void print_debug_details(std::ostream& o, const int& v, bool verbose)
//   {
//       if (verbose)
//           o << "int @" << &v << " = " << v;
//       else
//           o << v;
//   }
//
//   int main()
//   {
//       int i = 12;
//
//       std::cout
//          << "test 1: " << debug::brief(i) << '\n'
//          << "test 2: " << debug::verbose(i) << std::endl;
//   }
//
// Compiling and running this example produces the following output:
//
//   $ ./example
//   test 1: 12
//   test 2: int @0xbfc1acfc = 12

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

