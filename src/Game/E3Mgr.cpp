#include "Game/E3Mgr.h"
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

bool E3Mgr::isDemoMode() const {
    if (is2017Demo()) {
        return true;
    }
    if (isRidDemo()) {
        return true;
    }

    return mForceDemoMode;
}

void E3Mgr::setIsDemoMode(bool demo_mode) {
    mForceDemoMode = demo_mode;
    PlacementMgr::sFlags.set(PlacementMgr::MgrStaticFlags::DemoMode);
    if (!demo_mode) {
        PlacementMgr::sFlags.reset(PlacementMgr::MgrStaticFlags::DemoMode);
    }
}

bool E3Mgr::is2017Demo() const {
    return sead::EnvUtil::getRomType() == "Show_2017_1st";
}

bool E3Mgr::isRidDemo() const {
    return sead::EnvUtil::getRomType() == "RID_Demo";
}

void E3Mgr::clear28() {
    _28 = 0;
}

void E3Mgr::set28() {
    _28 = 1;
}

bool E3Mgr::isDemoMode0AndNotStageSelect() const {
    return isDemoMode() && mDemoMode == 0 && !isStageSelectState();
}

bool E3Mgr::isDemoMode1AndNotStageSelect() const {
    return isDemoMode() && mDemoMode == 1 && !isStageSelectState();
}

bool E3Mgr::isDemoMode2AndNotStageSelect() const {
    return isDemoMode() && mDemoMode == 2 && !isStageSelectState();
}

bool E3Mgr::is28One() const {
    return _28 == 1;
}

bool E3Mgr::isRidDemoAnd28IsOne() const {
    return isRidDemo() && is28One();
}

bool E3Mgr::isRidDemoAnd28IsOne_() const {
    return isRidDemo() && is28One();
}

bool E3Mgr::isRidDemoAnd6fIsNonzero() const {
    return isRidDemo() && _6f != 0;
}

s32 E3Mgr::getDemoStage() const {
    if (isDemoMode() && mDemoMode == 2 && !isStageSelectState()) {
        return mDemoStage;
    }
    return -1;
}

void E3Mgr::setDemoStage(s32 demo_stage) {
    mDemoStage = demo_stage;
}

void E3Mgr::setDemoMode(s32 demo_mode) {
    mDemoMode = demo_mode;
}

void E3Mgr::setTimerMaybe(s32 a2) {
    _2C = a2;
}

s32 E3Mgr::get2C() const {
    return _2C;
}

void E3Mgr::loadBuildTimeStubbed() {
    ksys::res::LoadRequest req;

    req._21 = true;
    req._22 = true;
    req.mLoadCompressed = true;
    req.mRequester = "E3Mgr";
    req.mPath = "System/BuildTime.txt";
}

s32 E3Mgr::resIsReady() {
    return true;
}

void E3Mgr::setEmptyStr() {
    mStr = sead::SafeStringBase<char>::cEmptyString;
}

void E3Mgr::setIsRidDemo(bool a2) {
    if (isRidDemo()) {
        mIsRidDemo2 = a2;
    }
}

void E3Mgr::set6C(bool a2) {
    _6c = a2;
}

void E3Mgr::_auto2() {
    _auto3();
    _6d = 0;
}

//! TODO : this should be a real struct
struct Dummy {
    char _0[0xA00];
    u32 a00;
};

extern Dummy* test;

void E3Mgr::_auto3() {
    bool is_demo;

    _6a = 0;
    _68 = 0;
    _69 = 0;
    _6e = 0;
    _6f = 0;
    mIsRidDemo = false;
    mIsRidDemo2 = false;

    if (!isRidDemo() || !_6c) {
        mTick1.setNow();
    }
    mTick2.setNow();
    mTick3.setNow();
    mTick4.setNow();
    _30 = -2;
    is_demo = isDemoMode();
    if (is_demo) {
        if (test)
            test->a00 |= 0x40;
    }
}

}  // namespace uking
