#include "E3MGR.hpp"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "controller/seadController.h"
#include "devenv/seadEnvUtil.h"
#include "prim/seadSafeString.h"

extern bool isStageSelectState();

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
    // TODO look into the flag being u16
    ksys::map::PlacementMgr::sFlags.set(ksys::map::PlacementMgr::MgrStaticFlags::DemoMode);
    if (!demoMode) {
        ksys::map::PlacementMgr::sFlags.reset(ksys::map::PlacementMgr::MgrStaticFlags::DemoMode);
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
    if (E3Mgr::isDemoMode() && _24 == 0) {
        return !isStageSelectState();
    } else {
        return false;
    }
}

bool E3Mgr::__auto0() {
    if (E3Mgr::isDemoMode() && _24 == 1) {
        return !isStageSelectState();
    } else {
        return false;
    }
}

bool E3Mgr::__auto9() {
    if (E3Mgr::isDemoMode() && _24 == 2) {
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

bool E3Mgr::isRID_Demo_and_a1x6f_is_nonzero() {
    if (isRID_Demo()) {
        return _6f != 0;
    } else {
        return false;
    }
}

s32 E3Mgr::__auto4() {
    if ((isDemoMode()) && (_24 == 2) && (isStageSelectState() == 0)) {
        return _100;
    } else {
        return 0xFFFFFFFF;
    }
}

void E3Mgr::setDemoStage(s32 a2) {
    _100 = a2;
}

void E3Mgr::setDemoMode(s32 a2) {
    _24 = a2;
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



/*
E3Mgr * E3Mgr::sub_71008A6EE8()
{
  int v2; // w21
  sead::SafeStringBase<char> *RomType; // x20
  char *mStringTop; // x8
  int v5; // w23
  __int64 i; // x9
  int v7; // w10
  int v8; // w25
  bool v9; // w20
  char v10; // w0
  _QWORD *p_tick2; // x20
  sead::SafeStringBase<char> *v12; // x20
  char *v13; // x8
  __int64 j; // x9
  int v15; // w10
  char *p_isRIDDemo; // x8

  if ( _30 <= (signed int)0xFFFFFFFE )
    v2 = _2C;
  else
    v2 = _30;
  if (v2 >= 0 ) //(v2 & 0x80000000) == 0 ?
  {
    RomType = sead::EnvUtil::getRomType();
    RomType->assureTerminationImpl_(RomType);
    RomType->assureTerminationImpl_(RomType);
    mStringTop = RomType->mStringTop;
    if ( mStringTop != "RID_Demo" )
    {
      v5 = (unsigned __int8)sead::SafeStringBase<char>::cNullChar;
      for ( i = 0LL; i < 0x80001; ++i )
      {
        v7 = (unsigned __int8)mStringTop[i];
        if ( v7 != (unsigned __int8)aRidDemo[i] )
          break;
        if ( v7 == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
          goto LABEL_24;
      }
      v8 = sead::SeadController::getInstance()->_._.field_110;
      v9 = sub_71008A7094();
      v10 = sub_71008BB830();
      if ( v9 || !v8 || (v10 & 1) != 0 )
      {
        mTick2.setNow();
        p_tick2 = &v1->tick2;
      }
      else
      {
        p_tick2 = &v1->tick2;
      }
      if ( (nn::os::GetSystemTick() - *p_tick2) / sead::TickSpan::cFrequency >= 120 )
      {
        if(isRID_Demo()) {
            isRIDDemo2 = true;
        } else {
            _69 = true;
        }
      }
    }
LABEL_24:
    result = (E3Mgr *)nn::os::GetSystemTick();
    if ( v2 <= ((__int64)result - v1->tick1) / sead::TickSpan::cFrequency )
      _6a = 1;
  }
  return result;
}
*/
}  // namespace uking