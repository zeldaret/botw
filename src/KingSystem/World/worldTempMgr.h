#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"
#include "worldDefines.h"

namespace ksys::world {

// Status TODO:
// MISSING TempMgr::calcType2_()
//
// Non-matching TempMgr::TempMgr~()
class TempMgr : public Job {
    SEAD_RTTI_OVERRIDE(TempMgr, Job)
public:
    TempMgr();
    ~TempMgr() override;

    void reset();
    void x();

    void setInstantTemperature();

    static float calcRandomMoisture();

protected:
    JobType getType() const override { return JobType::Temp; }
    float calcTemperature();
    void calcType1_() override;
    void calcType2_() override;
    void calc_() override;
    void init_(sead::Heap* heap) override;
    void m8_null();

    float getStepValue() const;

    float _20;
    VFRValue mVFRTemperature;
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
    int _7c;
    float _80;
    float _84;
    float _88;
};
KSYS_CHECK_SIZE_NX150(TempMgr, 0x90);

}  // namespace ksys::world
