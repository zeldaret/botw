#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {
class TempMgr : public Job {
    SEAD_RTTI_OVERRIDE(TempMgr, Job)
public:
    TempMgr();
    ~TempMgr() override;

    void reset();
    void setInstantTemperature();

protected:
    JobType getType() const override { return JobType::Temp; }
    void calcType1_() override;
    void calcType2_() override;
    void calc_() override;
    void init_(sead::Heap* heap) override;

    void m8_null();
    void x();

    float getStepValue() const;
    float calcTemperature();
    static float calcRandomMoisture();

private:
    float mTemperature2;
    VFRValue mVFRTemperature;
    float mWeatherOffset;
    float mPlayerElevation;
    float mHumidity;
    float mTemperature;
    float _40;
    float _44;
    VFRValue _48;
    float mStepValue;
    float mTempAddValue;
    float mTempAddEnd;
    float mTempExtreme;
    s32 mSpeedupTimer;
    int mCurrentHour;
    Climate mCurrentClimate;
    float mMoisture;
    float _74;
    float _78;
    int _7c;
    float _80;
    float mBloomThreshold;
    float mBloomIntensity;
};
KSYS_CHECK_SIZE_NX150(TempMgr, 0x90);

}  // namespace ksys::world
