#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Resource/Actor/resResourceLod.h"
#include "KingSystem/System/OcclusionQueryCylinder.h"

namespace ksys::act {

// NON_MATCHING: reorders at the beginning because of initFlags -- should be equivalent
LodState::LodState(sead::Heap* heap, sead::BitFlag32 flags, Actor* actor,
                   int disable_calc_skip_frame, float x)
    : mFlags14(flags), mActor(actor), _44(x), mDisableCalcSkipFrame(disable_calc_skip_frame) {
    initFlags();

    if (mActor->getProfile().include("Enemy") || mActor->getProfile().include("Swarm") ||
        mActor->getProfile().include("EnemySwarm")) {
        _24 = 0;
    }
    if (mActor->getProfile().include("NPC")) {
        _24 = 1;
    }
    if (mActor->getName() == "GameRomHorseBone") {
        _24 = 1;
    }
    _25 = _24;

    if (mActor->getMapObject()) {
        mDispDistance = mActor->getMapObject()->getDispDistance();
    }

    const bool is_air_octa_platform = isAirOctaPlatform(mActor->getName());
    if (!mActor->checkFlag(Actor::ActorFlag::_39) || mActor->getProfile().startsWith("Guardian")) {
        if (is_air_octa_platform) {
            mOcclusionQueryCylinder = new (heap) OcclusionQueryCylinder;
            mOcclusionQueryCylinder->init(heap);
        }
    } else {
        mOcclusionQueryCylinder = new (heap) OcclusionQueryCylinder;
        mOcclusionQueryCylinder->init(heap);
    }

    if (is_air_octa_platform)
        mFlags26.set(0x40);

    if (auto* lod = mActor->getParam()->getRes().mLod) {
        if (lod->mDisableConstActor.ref())
            mFlags14.set(0x1000000);
        mDistanceScale = lod->mDistanceScale.ref();
        if (lod->mDisableCalcRescueDistLimit.ref())
            mFlags14.set(0x4000000);
    }

    int type = 8;
    if (mActor->getProfile().include("Giant") || mActor->getProfile().include("Guardian")) {
        type = 1;
    } else if (mActor->getProfile().include("Enemy") || mActor->getProfile().include("Swarm") ||
               mActor->getProfile().include("EnemySwarm")) {
        type = 0;
    } else if (mActor->getProfile() == "NPC") {
        type = 2;
    } else if (mActor->getProfile().include("Horse")) {
        type = 7;
    } else if (mActor->getName().include("Insect")) {
        type = 4;
    } else if (mActor->getName().include("Fish")) {
        type = 5;
    } else if (mActor->getName().include("Weapon")) {
        type = 6;
    } else if (mActor->getName().include("Animal")) {
        type = 3;
    }
    mActorType = type;
    _70 = 60;

    float dist = 500.0f;

    if (!hasTag(mActor, tags::Door)) {
        if (mActor->getName() == "SignalFireWood" ||
            mActor->getName() == "DgnObj_EntranceShutter_A_01" ||
            mActor->getName() == "DgnObj_WarpPoint_A_01" ||
            mActor->getName() == "DgnObj_EntranceTerminal_A_01" ||
            mActor->getName().startsWith("DgnObj_DungeonEntrance_A_01") ||
            mActor->getName().startsWith("DgnObj_RemainsLithograph_A") ||
            mActor->getName().startsWith("DgnObj_RemainsLithogragh_A") ||
            mActor->getName() == "GreatFairyBeforeRevival" ||
            mActor->getName() == "TwnObj_FairySpringClose_A_01" ||
            mActor->getName() == "TwnObj_FairySpring_A_01" ||
            mActor->getName() == "Rito_BrosRock_Relief" ||
            mActor->getName() == "TwnObj_HyruleCastleSealCover_A_01" ||
            mActor->getName() == "FldObj_DownloadTerminalBody_A_01" ||
            mActor->getName() == "FldObj_DownloadTerminal_A_01" ||
            mActor->getName() == "FldObj_MapTowerWingBefore_A_01" ||
            mActor->getName() == "FldObj_MapTower_A_01" ||
            mActor->getName().startsWith("Item_CookSet") ||
            mActor->getName() == "DgnObj_WarpPointSP" ||
            mActor->getName() == "DgnObj_EntranceTerminalSP" ||
            mActor->getName() == "DgnObj_EntranceShutterSP" ||
            mActor->getName() == "DgnObj_EntranceElevatorSP" ||
            mActor->getName() == "DgnObj_DLC_ChampionsDungeonEntrance_A_01" ||
            mActor->getName().startsWith("FldObj_DLC_HeroMapRelief_Mark_A") ||
            mActor->getName().startsWith("FldObj_DLC_HeroMap_") ||
            mActor->getName() == "FldObj_DLC_HeroMapRelief_A_01") {
            _70 = 60;
            dist = 10.0f;
        } else if (mActor->getName() == "Bros_Rock_01" || mActor->getName() == "Bros_Rock_02" ||
                   mActor->getName() == "Bros_Rock_03" || mActor->getName() == "Bros_Rock_04" ||
                   mActor->getName() == "Bros_Rock_05") {
            _70 = 60;
            dist = 30.0f;
        } else if (mActor->getName() == "TwnObj_GanonGrudgeSolid_Eyeball_A_01") {
            _70 = 60;
            dist = 110.0f;
        } else if (mActor->getName().include("TwnObj_HyruleCastleObject") ||
                   mActor->getName().include("TwnObj_HyruleCastle_GateBridgeDoor")) {
            _70 = 60;
            dist = 50.0f;
        } else if (mActor->getName() == "WallCrack" || mActor->getName() == "Obj_RockBroken_A_02" ||
                   mActor->getName() == "TwnObj_HyruleCastleSealCover_A_01" ||
                   mActor->getName() == "TwnObj_HyruleCastleMap_BossModel_A_01") {
            _70 = 120;
            dist = 100.0f;
        } else if (mActor->getName().startsWith("MergedGrudge") && mActor->getMapObject()) {
            int field_body_group = -1;
            mActor->getMapObject()->getMubinIter().tryGetParamIntByKey(&field_body_group,
                                                                       "FieldBodyGroup");
            if (field_body_group >= 0) {
                dist = 500.0f;
            } else {
                _70 = 60;
                dist = 10.0f;
            }
        } else if (mActor->getName() == "FldObj_GoronCannonSwitch_A_01" ||
                   mActor->getName() == "FldObj_GoronCannon_A_01") {
            _70 = 120;
            dist = 50.0f;
        } else if (mActor->getName().startsWith("Mannequin_")) {
            _70 = 120;
            dist = 5.0f;
        } else if (mActor->getName().startsWith("KorokAnswerResponce") ||
                   mActor->getName().startsWith("FldObj_AreaStopClimbing")) {
            _70 = 900;
            dist = 0.0f;
        } else if (is_air_octa_platform) {
            _24 = 0;
            u32 hashid = 0;
            if (!actor->getMapObjIter().tryGetParamUIntByKey(&hashid, "HashId") ||
                (hashid != 0x8F7A380B && hashid != 0x57F2CB61)) {
                _78 = 85.0f;
                mFlags26.set(0x30);
            }
        }
    }

    auto* pm = map::PlacementMgr::instance();
    map::PlacementStruct1* ps1 = nullptr;
    if (pm && pm->mPlacementActors && (ps1 = pm->mPlacementActors->mStruct1)) {
        if (!ps1->mIsOneHitChallengeActive) {
            if (ps1->mFlags.isOnBit(15)) {
                if (actor->getName() == "DgnObj_DLC_IbutsuEx_Candle_A_01" ||
                    actor->getName() == "TBox_Dungeon_Stone" ||
                    actor->getName() == "DgnObj_DLC_SwordLight_A_01") {
                    _70 = 240;
                    dist = 10.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuExLava_A_01" ||
                           actor->getName() == "DgnObj_DLC_SwitchStep_A_01" ||
                           actor->getName() == "DgnObj_DLC_CapShutter" ||
                           actor->getName() == "DgnObj_DLC_IbutsuExD_AncientBallSwitch_A_01" ||
                           actor->getName() == "DungeonPit") {
                    _70 = 120;
                    dist = 50.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_F_GoalSystem_A_01" ||
                           actor->getName() == "DgnObj_DLC_GoalShield_A" ||
                           actor->getName() == "Npc_DungeonPriestDlc2nd_Boss" ||
                           actor->getName() == "DgnObj_DLC_IbutsuExFloor_A_02") {
                    _70 = 15;
                    dist = 30.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuExOutWall_A_01") {
                    _70 = 240;
                    dist = 0.0f;
                } else if (actor->getName().include("CylinderWall")) {
                    _70 = 240;
                    dist = 65.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_A_01") {
                    _70 = 240;
                    dist = 125.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_F_02") {
                    _70 = 60;
                    dist = 30.0f;
                } else if (actor->getName() == "DgnObj_RemainsTerminalBody_A" ||
                           actor->getName() == "FldObj_Terminal_A_01" ||
                           actor->getName() == "DgnObj_DLC_ShutterFence_A_01" ||
                           actor->getName() == "FldObj_DownloadTerminal_A_01" ||
                           actor->getName() == "EventTag") {
                    _70 = 60;
                    dist = 30.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_E_Faucet_A_01" ||
                           actor->getName() == "DgnObj_DLC_IbutsuEx_E_Faucet_A_02" ||
                           actor->getName() == "SwitchTimeLag" || actor->getName() == "Area" ||
                           actor->getName() == "ActorObserverTag") {
                    _70 = 60;
                    dist = 80.0f;
                } else if (actor->getName() == "DgnObj_DLC_ShutterFence_A_01" ||
                           actor->getName() == "DgnObj_DLC_ShutterFenceFrame_A_01") {
                    _70 = 60;
                    dist = 120.0f;
                } else if (actor->getName() == "DgnObj_ElectricCable_FinalTrial" ||
                           actor->getName() == "DgnObj_SwitchElectric0_FinalTrial" ||
                           actor->getName() == "DgnObj_DLC_IbutsuEx_B_ElectricWire_A_02") {
                    _70 = 60;
                    dist = 90.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_B_MagnePoleAcceptor_A_01") {
                    _70 = 60;
                    dist = 75.0f;
                } else if (actor->getName() == "ElectricGenerator") {
                    _70 = 60;
                    dist = 35.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuExD_Hole_A_02") {
                    _70 = 60;
                    dist = 100.0f;
                } else if (actor->getName() == "DgnObj_AncientBall_B_01") {
                    _70 = 60;
                    dist = 90.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEXD_FirePillar_A_01" ||
                           actor->getName() == "DgnObj_DLC_IbutsuEXD_FirePillar_A_02") {
                    _70 = 60;
                    dist = 75.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuExD_WallSpike_A_01" ||
                           actor->getName() == "DgnObj_DLC_IbutsuExD_Cylinder_A_01") {
                    _70 = 60;
                    dist = 60.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_E_WaterPump_A_01" ||
                           actor->getName() == "DgnObj_DungeonWater50x50_A_01") {
                    _70 = 60;
                    dist = 100.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_E_WaterPump_A_02") {
                    _70 = 60;
                    dist = 140.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_E_WaterPump_A_03") {
                    _70 = 60;
                    dist = 75.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_E_Shaft_A_01" ||
                           actor->getName() == "DgnObj_DLC_IbutsuObj_StonePoleAcceptor_A_01") {
                    _70 = 60;
                    dist = 50.0f;
                } else if (actor->getName() == "DgnObj_DLC_IbutsuEx_E_Scaffold_A_02" ||
                           actor->getName() == "DgnObj_DLC_IbutsuEx_E_Scaffold_A_03") {
                    _70 = 60;
                    dist = 60.0f;
                }
            }
        } else {
            if (actor->getName() == "FldObj_FlagLarge_A_01") {
                _70 = 120;
                dist = 70.0f;
            } else if (actor->getName() == "FldObj_SoilRock_MapTower_A_01" ||
                       actor->getName() == "TwnObj_HunterHouseLamp_A_02") {
                _70 = 900;
                dist = 0.0f;
            } else if (actor->getName() == "TwnObj_GoddesStatue_A_01" ||
                       actor->getName() == "FireWoodDie") {
                _70 = 120;
                dist = 50.0f;
            } else if (actor->getName().include("FenceWoodDamage") ||
                       actor->getName().startsWith("FldObj_Damage")) {
                _70 = 30;
                dist = 13.0f;
            } else if (actor->getName().include("ShieldFence")) {
                _70 = 30;
                dist = 30.0f;
            }
        }
    }
    _6c = dist * dist;

    float value_68 = 1.0;
    if (mActor->getName().startsWith("Enemy_Lynel")) {
        value_68 = 2.0;
    }
    _68 = value_68;

    if (actor->getName() == "Npc_RitoHatago001" || actor->getName() == "Npc_TabantaHatago001" ||
        actor->getName() == "Npc_FaronWoods001") {
        mFlags8.set(0x100000000);
    }

    if (actor->getName().startsWith("Npc_Zora") && !actor->getName().isEqual("Npc_Zora003") &&
        !actor->getName().isEqual("Npc_ZoraB001") && !actor->getName().isEqual("Npc_Zora004")) {
        mFlags8.set(0x200000000);
    }

    _74 = 0.0f;
    if (actor->checkFlag(Actor::ActorFlag::_29) && actor->getProfile() == "NPC") {
        _74 = 900.0f;
    }

    if (actor->getName().startsWith("FldObj_FlagLarge")) {
        _50 = 3.0f;
    }
}

LodState::~LodState() {
    if (mOcclusionQueryCylinder)
        delete mOcclusionQueryCylinder;
}

// NON_MATCHING: ????? reordering
void LodState::initFlags() {
    _28 = 1.0;
    _40 = 0.0;
    mFlags26.reset(2);
    mFlags8.set(0xFFFFFFFF'00000000);
    if (!mFlags8.isOn(0x20000000)) {
        mFlags8.reset(0xEFFFFFFF);
        mFlags8.set(0xCFC360BF);
        mFlags8.reset(0x40);
    } else {
        mFlags8.set(0xEFFFFFFF);
        mFlags8.set(0xEFC360BF);
        mFlags8.reset(0x40);
    }
    mFlags8.reset(0x3C9F00);
    mFlags8.set(0x4000);
    mFlags14.set(0x2000000);
    _60 = 0xFFFF;
    _64 = -3;
}

}  // namespace ksys::act
