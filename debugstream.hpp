
#ifndef DEBUG_STREAM_HPP_included
#define DEBUG_STREAM_HPP_included

//! \file
//! A simple mechanism for writing debug info to an output stream.
//!
//! Use Standard Library output streams to output debug information
//! without defining explicit <tt>operator<<()</tt> overloads.  Instead,
//! wrap instances of \c T in calls to \c debug::brief() and
//! \c debug::verbose() when writing to the output stream.  Then simply
//! implement
//! <tt>void print_debug_details(std::ostream&, T&, bool verbose)</tt>
//! for the type \c T you are interested in.  The \c verbose flag
//! can be observed to provide distinct brief and verbose output
//! levels are desired.
//!
//! An example implementation for \c int values:
//!
//! \code
//! #include "debugstream.hpp"
//!
//! #include <iostream>
//!
//! void print_debug_details(std::ostream& o, const int& v, bool verbose)
//! {
//!     if (verbose)
//!         o << "int @" << &v << " = " << v;
//!     else
//!         o << v;
//! }
//!
//! int main()
//! {
//!     int i = 12;
//!
//!     std::cout
//!         << "test 1: " << debug::brief(i) << '\n'
//!         << "test 2: " << debug::verbose(i) << std::endl;
//! }
//! \endcode
//!
//! Compiling and running this example produces the following output:
//!
//! \code
//! $ ./example
//! test 1: 12
//! test 2: int @0xbfc1acfc = 12
//! \endcode

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

    //! \brief Provide brief output on an ouput stream.
    //! \param value The value to output for.
    template <typename T>
    detail::Streamer<T> brief(const T& value)
    {
        return detail::Streamer<T>(value, false);
    }

    //! \brief Provide verbose output on an ouput stream.
    //! \param value The value to output for.
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

#endif  // DEBUGSTREAM_HPP_included
