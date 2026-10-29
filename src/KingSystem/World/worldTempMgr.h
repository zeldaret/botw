#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"
#include "worldDefines.h"

namespace ksys::world {

// Status TODO:
// MISSING TempMgr::reset()
// MISSING TempMgr::x()
// MISSING TempMgr::m8_null()
//
// Non-matching TempMgr::getStepValue()
// Non-matching TempMgr::calc2()
// Non-matching TempMgr::TempMgr~()
//
// ???? TempMgr::getType() - Should be matching, but it's not compiled into uking?
//
// MATCHES TempMgr::loadInfo()
// MATCHES TempMgr::TempMgr()
// MATCHES TempMgr::calcRandomMoisture();
// MATCHES TempMgr::calc_()
// MATCHES TempMgr::calcTemperature();
// MATCHES TempMgr::calc1()
// MATCHES TempMgr::setInstantTemperature()
class TempMgr : public Job {
public:
    TempMgr();
    ~TempMgr() override;

    void reset();

    void setInstantTemperature();

    static float calcRandomMoisture();

protected:
    JobType getType() const override { return JobType::Temp; }
    float calcTemperature();
    void calc1();
    void calc2();
    void calc_() override;
    void loadInfo();

    float getStepValue() const;

    float _20;
    VFRValue _24;
    float mWeatherOffset;
    float mPlayerElevation;
    s32 _38;
    float _3c;
    float _40;
    float _44;
    VFRValue _48;
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
    float _7c; // UNSURE This might be a VFR value?
    float _80; // UNSURE
    float _84; // UNSURE
    float _88;
};
KSYS_CHECK_SIZE_NX150(TempMgr, 0x90);

}  // namespace ksys::world
