#ifndef OXF_OMREACTIVE_H
#define OXF_OMREACTIVE_H

#include <oxf/oxf.h>
#include <QObject>

struct OMReactive {
    inline bool startBehavior() { return true; }
    inline void destroy() {}
};
typedef QObject IOxfActive;

#endif
