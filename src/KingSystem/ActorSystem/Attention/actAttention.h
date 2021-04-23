#pragma once

#include <prim/seadEnum.h>

namespace ksys::act {

enum class AttType {
    Action = 0,
    Lock = 1,
    SwordSearch = 2,
    Attack = 3,
    Appeal = 4,
    JumpRide = 5,
    NameBalloon = 6,
    LookOnly = 7,
    Invalid = 8,
};

// Make sure to update AttActionType if this is changed
enum class AttActionCode {
    None = 0x1800000,
    Talk,
    Listen,
    Awake,
    Grab,
    Open,
    Pick,
    Catch,
    CheckCatch,
    CatchWeapon,
    Skin,
    Sleep,
    Sit,
    Lumber,
    Pushpull,
    Read,
    Check,
    Boot,
    BootPStop,
    Leave,
    Remind,
    Buy,
    Ride,
    Wakeboard,
    WakeboardRide,
    RideRito,
    RideZora,
    Cook,
    KillTime,
    Display,
    DisplayBow,
    DisplayShield,
    PickUp,
    Pray,
    PullOut,
    Waterfall,
    CommandWait,
    CommandCome,
    Thrust,
    Put,
    PickToEvent,
    Dummy,
};

// clang-format off
SEAD_ENUM(AttActionType, None,Talk,Listen,Awake,Grab,Open,Pick,Catch,CheckCatch,CatchWeapon,Skin,Sleep,Sit,Lumber,Pushpull,Read,Check,Boot,BootPStop,Leave,Remind,Buy,Ride,Wakeboard,WakeboardRide,RideRito,RideZora,Cook,KillTime,Display,DisplayBow,DisplayShield,PickUp,Pray,PullOut,Waterfall,CommandWait,CommandCome,Thrust,Put,PickToEvent,Dummy)
SEAD_ENUM(AttPriorityType, Default,Enemy,Npc,Obj,ObjLow,ObjMiddle,ObjHigh,Bullet)
// clang-format on

}  // namespace ksys::act
