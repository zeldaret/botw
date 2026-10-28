#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"
#include "worldDefines.h"

namespace ksys::world {

// Status TODO:
// MISSING TempMgr::TempMgr~()
// MISSING TempMgr::reset()
// MISSING TempMgr::x()
// MISSING TempMgr::m8_null()
// MISSING TempMgr::loadInfo()
//
// Non-matching TempMgr::TempMgr()
// Non-matching TempMgr::getStepValue()
// Non-matching TempMgr::calc2()
//
// ???? TempMgr::getType() - Should be matching, but it's not compiled into uking?
//
// MATCHES TempMgr::calcRandomMoisture();
// MATCHES TempMgr::calc_()
// MATCHES TempMgr::calcTemperature();
// MATCHES TempMgr::calc1()
// MATCHES TempMgr::setInstantTemperature()
class TempMgr : public Job {
public:
    TempMgr();
    ~TempMgr();


    void reset();

    void setInstantTemperature();

    static float calcRandomMoisture();

protected:
    JobType getType() const override { return JobType::Temp; }
    float calcTemperature();
    void calc1();
    void calc2();
    void calc_() override;

    float getStepValue() const;

    float _20;
    VFRValue _24;
    float mWeatherOffset;   // 0x30
    float mPlayerElevation; // 0x34
    s32 _38;
    float _3c;
    float _40;
    float _44;
    u8 _48[0x4c - 0x48];
    float _4c;
    u8 _50[0x54 - 0x50];
    float mStepValue;
    float mTempMax;
    float mTempMin;
    float _60;
    s32 mSpeedupTimer;
    int mCurrentHour;
    Climate mCurrentClimate;
    float mMoisture;
    float _74;
    float _78;
    u8 _7c[12];
    float _88;
};
KSYS_CHECK_SIZE_NX150(TempMgr, 0x90);

}  // namespace ksys::world
