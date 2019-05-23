#ifndef OXF_OMTHREAD_H
#define OXF_OMTHREAD_H

#include <oxf/oxf.h>

struct OMThread {};

template <>
const bool isThreadObj<OMThread>::value = true;

//#define OMThread QThread

#endif
