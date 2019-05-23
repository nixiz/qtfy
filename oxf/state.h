#ifndef OXF_OMSTATE_H
#define OXF_OMSTATE_H

#include <Rh/RhState.h>
#include <Rh/RhTimerState.h>
#include <Rh/RhConditionState.h>
#include <Rh/RhTransitions.hpp>

#define RH_CREATE_STATE(statename, ...) \
    RhState *statename = new RhState(EXPAND_TO_STRING(statename), __VA_ARGS__)
#define RH_CREATE_TIMER_STATE(statename, tInterval, ...) \
    RhTimerState *statename = new RhTimerState(tInterval, EXPAND_TO_STRING(statename), __VA_ARGS__)
#define RH_CREATE_COND_STATE(statename, ...) \
    RhConditionState *statename = new RhConditionState(EXPAND_TO_STRING(statename), __VA_ARGS__)
#define IS_IN(state) isInState(#state)

#endif
