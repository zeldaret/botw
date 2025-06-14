#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "container/seadRingBuffer.h"

namespace ksys::act {

class Actor;
class PlayerBase;

class PlayerInfoBase {
public:
    PlayerInfoBase();
    virtual ~PlayerInfoBase();
};

class PlayerInfo : public PlayerInfoBase {
    SEAD_SINGLETON_DISPOSER(PlayerInfo)
    PlayerInfo();
    ~PlayerInfo() override;

public:
    BaseProcLink& getPlayerLink() { return mPlayerLink; }
    bool init();
    void setAndAcquirePlayer(PlayerBase* player);  // requires PlayerOrEnemy and PlayerBase
    void resetPlayer(PlayerBase* player);
    bool acquireHorse(BaseProc* horse);
    void setHorseLink(const BaseProcLink& horse_link);
    PlayerBase* getPlayer() const;
    PlayerBase* getPlayer_() const;                // possibly duped by compiler?
    Actor* getRiddenHorse() const;                 // requires PlayerBase vtable
    void setMaxLifeForPlayerActor(s32 max_heart);  // requires PlayerBase
    s32 getMaxLifeFromPlayerActor() const;
    void setMaxHeartValue(s32 quarter_hearts);
    u32 getMaxHeartValue() const;
    void updateMaxHeartValueFromGameData();
    void setLifeForPlayerActor(s32 life);
    s32 getLifeFromPlayerActor() const;
    void updateCurrentHartFlagFromPlayerActor();  // TODO
    void updateLifeAfterGameOver();               // requires a global flag
    void
    resetLifeToBeforeSwordPull();     // requires HeartDisplayMgr (0x25D6578) and PlayerBase vtable
    void saveLifeInfoForSwordPull();  // requires PlayerBase vtable
    void recoverLife();
    void setStaminaCurrentMax(f32 max_stamina);
    f32 getStaminaCurrentMax() const;
    void updateStaminaCurrentMaxFromGameData();
    void setStaminaMax(f32 max_stamina);
    f32 getStaminaMax() const;
    void updateStaminaMaxFromGameData();
    void setMaxStaminaForPlayerActor(f32 max_stamina);  // requires PlayerBase
    f32 getMaxStaminaFromPlayerActor() const;           // requires PlayerBase
    void recoverStamina();                              // requires PlayerBase
    void recoverCondition();                            // requires PlayerBase

    PlayerBase* getPlayerUnchecked();

    sead::Vector3f& getPlayerPos();
    sead::Vector3f& getPlayerPosForPostCalc();

    // TODO: name and PlayerBase vtable
    sead::Vector3f& getPlayerM265();

private:
    // These are probably debug stuff that were removed
    class Info1 : public PlayerInfoBase {
    public:
        Info1();
        ~Info1() override;
    } mInfo1;
    class Info2 : public PlayerInfoBase {
    public:
        Info2();
        ~Info2() override;
    } mInfo2;
    class Info3 : public PlayerInfoBase {
    public:
        Info3();
        ~Info3() override;
    } mInfo3;
    class Info4 : public PlayerInfoBase {
    public:
        Info4();
        ~Info4() override;
    } mInfo4;
    class Info5 : public PlayerInfoBase {
    public:
        Info5();
        ~Info5() override;
    } mInfo5;
    class Info6 : public PlayerInfoBase {
    public:
        Info6();
        ~Info6() override;
    } mInfo6;
    class Info7 : public PlayerInfoBase {
    public:
        Info7();
        ~Info7() override;
    } mInfo7;
    PlayerBase* mPlayerActor = nullptr;
    BaseProcLink mPlayerLink;
    BaseProcLink mHorseLink;
    sead::Vector3f mPlayerPos{0, 0, 0};
    sead::Vector3f mPlayerPosForPostCalc{0, 0, 0};
    f32 mMaxHeartValue = 0;
    f32 mStaminaCurrentMax = 1000;  // 1000 = 1 wheel
    f32 mStaminaMax = 1000;
    f32 mLifeBeforeSwordPull = 0;
    f32 mExtraLifeBeforeSwordPull = 0;
    sead::FixedRingBuffer<sead::Vector3f, 60> mPreviousPositions;
    f32 _3a0 = 65535;
    f32 _3a4 = 65535;
    f32 _3a8 = -1;
};
KSYS_CHECK_SIZE_NX150(PlayerInfo, 0x3B0);

}  // namespace ksys::act
