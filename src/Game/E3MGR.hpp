#pragma once

#include <nn/os.h>

#include <heap/seadDisposer.h>
#include <basis/seadTypes.h>
#include <time/seadTickSpan.h>
#include <prim/seadSafeString.h>
#include <time/seadTickTime.h>

#include "KingSystem/Resource/resHandle.h"



namespace uking {

class E3Mgr {
    E3Mgr() = default;
    SEAD_SINGLETON_DISPOSER(E3Mgr)

    public:
    bool isDemoMode();
    void setIsDemoMode(bool demoMode);
    bool isRID_Demo();
    bool is2017Demo();

    void clear28();
    void set28();
    bool __auto1();
    bool __auto0();
    bool __auto9();
    void __auto2();
    void __auto3();

    void __auto8(bool a2);

    bool isRID_Demo_and_a1x28_is_one();
    bool isRID_Demo_and_a1x6f_is_nonzero();

    void setDemoStage(s32 a2);
    void setDemoMode(s32 a2);

    void setTimerMaybe(s32 a2);
    s32 resIsReady();

    s32 __auto5();
    s32 __auto4();

    void loadBuildTimeStubbed();

    void setEmptyStr();

    void setIsRIDDemo(bool a2);

    E3Mgr * sub_71008A6EE8();

    bool mForceDemoMode = false;
    u32 _24 = 0;
    u32 _28 = 0;
    u32 _2C = 1200;
    u32 _30 = 0xFFFFFFFE;
    sead::TickTime mTick1;
    sead::TickTime mTick2;
    sead::TickTime mTick3;
    sead::TickTime mTick4;
    sead::TickTime mTick5;
    sead::TickTime mTick6;
    u8 _68 = 0;
    u8 _69 = 0;
    u8 _6a = 0;
    bool isRIDDemo = false;
    u8 _6c = 0;
    u8 _6d = 1;
    u8 _6e = 0;
    u8 _6f = 0;
    bool isRIDDemo2 = false;

    sead::FixedSafeString<32> str;

    ksys::res::Handle handle;

    u32 _100 = 0xFFFFFFFF;
};

} //namespace uking
