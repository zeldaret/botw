#pragma once

#include <nn/os.h>

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <time/seadTickSpan.h>
#include <time/seadTickTime.h>

#include "KingSystem/Resource/resHandle.h"

namespace uking {

class E3Mgr {
    E3Mgr() = default;
    SEAD_SINGLETON_DISPOSER(E3Mgr)

public:
    bool isDemoMode() const;
    void setIsDemoMode(bool demoMode);
    bool isRidDemo() const;
    bool is2017Demo() const;

    void clear28();
    void set28();
    bool isDemoMode0AndNotStageSelect() const;
    bool isDemoMode1AndNotStageSelect() const;
    bool isDemoMode2AndNotStageSelect() const;
    void _auto2();
    void _auto3();

    void set6C(bool a2);

    bool isRidDemoAnd28IsOne() const;
    bool isRidDemoAnd28IsOne_() const;
    bool isRidDemoAnd6fIsNonzero() const;

    void setDemoStage(s32 demoStage);
    void setDemoMode(s32 demoMode);

    void setTimerMaybe(s32 a2);
    s32 resIsReady();

    s32 get2C() const;
    s32 getDemoStage() const;

    bool is28One() const;

    void loadBuildTimeStubbed();

    void setEmptyStr();

    void setIsRidDemo(bool a2);

    E3Mgr* sub_71008A6EE8();

private:
    bool mForceDemoMode = false;
    u32 mDemoMode = 0;
    u32 _28 = 0;
    s32 _2C = 1200;
    s32 _30 = -2;
    sead::TickTime mTick1;
    sead::TickTime mTick2;
    sead::TickTime mTick3;
    sead::TickTime mTick4;
    sead::TickTime mTick5;
    sead::TickTime mTick6;
    u8 _68 = 0;
    u8 _69 = 0;
    u8 _6a = 0;
    bool mIsRidDemo = false;
    u8 _6c = 0;
    u8 _6d = 1;
    u8 _6e = 0;
    u8 _6f = 0;
    bool mIsRidDemo2 = false;

    sead::FixedSafeString<32> mStr;

    ksys::res::Handle mHandle;

    s32 mDemoStage = -1;
};

}  // namespace uking
