#include "E3MGR.hpp"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "controller/seadController.h"
#include "devenv/seadEnvUtil.h"
#include "prim/seadSafeString.h"

/* Not yet attempted:
 * E3Mgr::calc - Requires SeadController and globals
 * sub_71008A6EE8 - Requires SeadController
 * sub_71008A7094 - Requires RTTI from not decompiled classes
 */

extern bool isStageSelectState();

using PlacementMgr = ksys::map::PlacementMgr;

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(E3Mgr)

bool E3Mgr::isDemoMode() {
    if (E3Mgr::is2017Demo()) {
        return true;
    }
    if (E3Mgr::isRID_Demo()) {
        return true;
    }

    return mForceDemoMode;
}

void E3Mgr::setIsDemoMode(bool demoMode) {
    mForceDemoMode = demoMode;
    PlacementMgr::sFlags.set(PlacementMgr::MgrStaticFlags::DemoMode);
    if (!demoMode) {
        PlacementMgr::sFlags.reset(PlacementMgr::MgrStaticFlags::DemoMode);
    }
}

bool E3Mgr::is2017Demo() {
    if (sead::EnvUtil::getRomType() == "Show_2017_1st") {
        return true;
    }
    return false;
}

bool E3Mgr::isRID_Demo() {
    if (sead::EnvUtil::getRomType() == "RID_Demo") {
        return true;
    }
    return false;
}

void E3Mgr::clear28() {
    _28 = 0;
}

void E3Mgr::set28() {
    _28 = 1;
}

bool E3Mgr::__auto1() {
    if (E3Mgr::isDemoMode() && mDemoMode == 0) {
        return !isStageSelectState();
    } else {
        return false;
    }
}

bool E3Mgr::__auto0() {
    if (E3Mgr::isDemoMode() && mDemoMode == 1) {
        return !isStageSelectState();
    } else {
        return false;
    }
}

bool E3Mgr::__auto9() {
    if (E3Mgr::isDemoMode() && mDemoMode == 2) {
        return !isStageSelectState();
    } else {
        return false;
    }
}

bool E3Mgr::isRID_Demo_and_a1x28_is_one() {
    if ((isRID_Demo() && (_28 == 1))) {
        return true;
    } else {
        return false;
    }
}

bool E3Mgr::isRID_Demo_and_a1x28_is_one_() {
    if ((isRID_Demo() && (_28 == 1))) {
        return true;
    } else {
        return false;
    }
}

bool E3Mgr::isRID_Demo_and_a1x6f_is_nonzero() {
    if (isRID_Demo()) {
        return _6f != 0;
    } else {
        return false;
    }
}

s32 E3Mgr::__auto4() {
    if ((isDemoMode()) && (mDemoMode == 2) && (isStageSelectState() == 0)) {
        return mDemoStage;
    } else {
        return 0xFFFFFFFF;
    }
}

void E3Mgr::setDemoStage(s32 demoStage) {
    mDemoStage = demoStage;
}

void E3Mgr::setDemoMode(s32 demoMode) {
    mDemoMode = demoMode;
}

void E3Mgr::setTimerMaybe(s32 a2) {
    _2C = a2;
}

s32 E3Mgr::__auto5() {
    return _2C;
}

void E3Mgr::loadBuildTimeStubbed() {
    ksys::res::LoadRequest req;

    req._21 = 1;
    req._22 = 1;
    req.mLoadCompressed = true;
    req.mRequester = "E3Mgr";
    req.mPath = "System/BuildTime.txt";
}

s32 E3Mgr::resIsReady() {
    return true;
}

void E3Mgr::setEmptyStr() {
    str = sead::SafeStringBase<char>::cEmptyString;
}

void E3Mgr::setIsRIDDemo(bool a2) {
    if (isRID_Demo()) {
        isRIDDemo2 = a2;
    }
}

void E3Mgr::__auto8(bool a2) {
    _6c = a2;
}

void E3Mgr::__auto2() {
     E3Mgr::__auto3();
    _6d = 0;
}

//! TODO : this should be a real struct
typedef struct dummy {
    char unk_0[0xA00];
    u32 unk_A00;
}dummy;

extern dummy* test;


void E3Mgr::__auto3() {
    bool isDemo;
    
    _6a = 0;
    _68 = 0;
    _69 = 0;
    _6e = 0;
    _6f = 0;
    isRIDDemo = false;
    isRIDDemo2 = false;
    
    if (!isRID_Demo() || !_6c) {
        mTick1.setNow();
    }
    mTick2.setNow();
    mTick3.setNow();
    mTick4.setNow();
    _30 = 0xFFFFFFFE;
    isDemo = E3Mgr::isDemoMode();
    if (isDemo) {
        if (test)
            (test->unk_A00) |= 0x40;
    }
}

}  // namespace uking