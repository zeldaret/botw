#pragma once

#include "math/seadBoundBox.h"
#include "math/seadVector.h"
#include "prim/seadBitFlag.h"
#include "prim/seadRuntimeTypeInfo.h"

namespace sead
{
class ControllerBase
{
    SEAD_RTTI_BASE(ControllerBase)
public:
    ControllerBase(int, int, int, int);

    void setRightStickCrossThreshold(float, float);
    void setPointerBound(const BoundBox2f& bound);
    void setPadRepeat(u32, u8, u8);
    void setLeftStickCrossThreshold(float, float);
    // unknown return type
    u32 getPadHoldCount(int) const;

    BitFlag32 getButtonsTrigger() const { return mButtonsTrigger; }
    BitFlag32 getButtonsRelease() const { return mButtonsRelease; }
    BitFlag32 getButtonsRepeat() const { return mButtonsRepeat; }
    BitFlag32 getButtonsHold() const { return mButtonsHold; }
    const Vector2f& getTouchScreenPos() const { return mTouchScreenPos; }
    const Vector2f& getLeftJoy() const { return mLeftJoy; }
    const Vector2f& getRightJoy() const { return mRightJoy; }

protected:
    void updateDerivativeParams_(u32, bool);
    void setPointerWithBound_(bool, bool, const Vector2f& bound);
    void setIdleBase_();
    bool isIdleBase_();
    // unknown return type
    u32 getStickHold_(u32, const Vector2f&, float, float, int);
    // unknown return type
    u32 createStickCrossMask_();

private:
    BitFlag32 mButtonsTrigger;
    BitFlag32 mButtonsRelease;
    BitFlag32 mButtonsRepeat;
    unsigned int mFlags;
    int _18;
    int _1c;
    BoundBox2f mPointerBound;
    int mPadHoldCounts[32];
    char _b0[32];
    char _d0[32];
    float mLeftStickThresholdX;
    float mRightStickThresholdX;
    float mLeftStickThresholdY;
    float mRightStickThresholdY;
    int _100;
    int _104;
    int _108;
    int _10c;
    unsigned int mIdleCounter;
    sead::BitFlag32 mButtonsHold;
    Vector2f mTouchScreenPos;
    Vector2f mLeftJoy;
    Vector2f mRightJoy;
    Vector2f _130;
};

}  // namespace sead
