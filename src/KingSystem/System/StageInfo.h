#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>

namespace ksys {

class StageInfo {
public:
    static void (*sChangeScene)(const sead::SafeString& map_name, const sead::SafeString& pos_name,
                                int x, bool triggered_by_stage_select);
    static bool sIsNotDebugStage;
    static bool sIsMainFieldDungeon;
    static bool sIsDungeon;
    static bool sIsCDungeon;
    static bool sIsMainFieldDungeon2;
    static bool sIsActorViewer;
    static bool sIsStageDebug;
    static bool sIsTestDungeon;
    static bool sIsDebugOrDevMap;
    static bool sIsRemainsElectric;
    static bool sIsRemainsFire;
    static bool sIsRemainsWater;
    static bool sIsRemainsWind;
    static bool sIsFinalTrial;
    static bool sIsAocField;
    static bool sIsMainField;
    static sead::FixedSafeString<32> sCurrentMapType;
    static sead::FixedSafeString<32> sCurrentMapName;
};

}  // namespace ksys
