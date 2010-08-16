
#ifndef __PARPORTTYPES_HH__
#define __PARPORTTYPES_HH__

#include <base/time.h>

namespace parport {

  struct StateChange {
    base::Time time;
    bool rising;
  };

};

#endif /*__PARPORTTYPES_HH__*/
