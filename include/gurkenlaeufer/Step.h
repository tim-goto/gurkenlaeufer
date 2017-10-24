#pragma once

#include "StepInterface.h"

#ifndef GURKE_STEP_NAME_PREFIX
#error GURKE_STEP_NAME_PREFIX has to be defined!
#endif

#define GURKE_STEP_INTERNAL(Name, Instance, RegEx)               \
    struct Name final : public gurkenlaeufer::detail::BaseStep { \
        Name()                                                   \
            : gurkenlaeufer::detail::BaseStep(RegEx, this)       \
        {                                                        \
        }                                                        \
        void runStep() override;                                 \
    } Instance;                                                  \
    void Name::runStep()

#define GURKE_BEFORE_HOOK_INTERNAL(Name, Instance, RegEx)                                                 \
    struct Name final : public gurkenlaeufer::detail::BaseHook<gurkenlaeufer::detail::Hooktype::Before> { \
        Name()                                                                                            \
            : gurkenlaeufer::detail::BaseHook<gurkenlaeufer::detail::Hooktype::Before>(RegEx, this)       \
        {                                                                                                 \
        }                                                                                                 \
        void runStep() override;                                                                          \
    } Instance;                                                                                           \
    void Name::runStep()

#define GURKE_AFTER_HOOK_INTERNAL(Name, Instance, RegEx)                                                 \
    struct Name final : public gurkenlaeufer::detail::BaseHook<gurkenlaeufer::detail::Hooktype::After> { \
        Name()                                                                                           \
            : gurkenlaeufer::detail::BaseHook<gurkenlaeufer::detail::Hooktype::After>(RegEx, this)       \
        {                                                                                                \
        }                                                                                                \
        void runStep() override;                                                                         \
    } Instance;                                                                                          \
    void Name::runStep()

#define GURKE_STR2(x) #x
#define GURKE_STR(x) x
#define GURKE_JOIN(X, Y) GURKE_DO_GURKE_JOIN(X, Y)
#define GURKE_DO_GURKE_JOIN(X, Y) GURKE_GURKE_DO_GURKE_JOIN2(X, Y)
#define GURKE_GURKE_DO_GURKE_JOIN2(X, Y) X##Y
#define STEP(RegEx)                                                                                   \
    GURKE_STEP_INTERNAL(                                                                              \
        GURKE_JOIN(GURKE_STR(GURKE_STEP_NAME_PREFIX), GURKE_JOIN(_Step, GURKE_STR(__COUNTER__))),     \
        GURKE_JOIN(GURKE_STR(GURKE_STEP_NAME_PREFIX), GURKE_JOIN(_Instance, GURKE_STR(__COUNTER__))), \
        RegEx)
#define BEFORE(RegEx)                                                                                   \
    GURKE_BEFORE_HOOK_INTERNAL(                                                                         \
        GURKE_JOIN(GURKE_STR(GURKE_STEP_NAME_PREFIX), GURKE_JOIN(_BeforeHook, GURKE_STR(__COUNTER__))), \
        GURKE_JOIN(GURKE_STR(GURKE_STEP_NAME_PREFIX), GURKE_JOIN(_Instance, GURKE_STR(__COUNTER__))),   \
        RegEx)
#define AFTER(RegEx)                                                                                   \
    GURKE_AFTER_HOOK_INTERNAL(                                                                         \
        GURKE_JOIN(GURKE_STR(GURKE_STEP_NAME_PREFIX), GURKE_JOIN(_AfterHook, GURKE_STR(__COUNTER__))), \
        GURKE_JOIN(GURKE_STR(GURKE_STEP_NAME_PREFIX), GURKE_JOIN(_Instance, GURKE_STR(__COUNTER__))),  \
        RegEx)
