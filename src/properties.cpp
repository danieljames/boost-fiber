//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/assert.hpp>
#include "boost/fiber/properties.hpp"
#include "boost/fiber/algorithm.hpp"
#include "boost/fiber/fiber_manager.hpp"
#include "boost/fiber/fiber_context.hpp"

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

void fiber_properties::notify()
{
    BOOST_ASSERT(sched_algo_);
    // Application code might change an important property for any fiber at
    // any time. The fiber in question might be ready, running or waiting.
    // Significantly, only a fiber which is ready but not actually running is
    // in the sched_algorithm's ready queue. Don't bother the sched_algorithm
    // with a change to a fiber it's not currently tracking: it will do the
    // right thing next time the fiber is passed to its awakened() method.
    if (fiber_->is_ready())
    {
        static_cast<sched_algorithm_with_properties_base*>(sched_algo_)->
            property_change_(fiber_, this);
    }
}

}}                                  // boost::fibers

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
