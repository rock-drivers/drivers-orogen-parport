
#ifndef __PARPORTTYPES_HH__
#define __PARPORTTYPES_HH__

#include <base/Time.hpp>

namespace parport {

  struct StateChange {
    base::Time time;
    bool rising;
  };

};

#endif /*__PARPORTTYPES_HH__*/
