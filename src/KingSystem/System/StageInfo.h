#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>

namespace ksys {

enum class StageType {
    Invalid = 0,
    OpenWorld = 1,
    Indoor = 2,
    OpenWorldTest = 3,
    MainFieldDungeon = 4,
    Viewer = 5,
};

class StageInfo {
public:
    static const sead::SafeString& getCurrentMapName();
    static const sead::SafeString& getCurrentMapType();

    static void setCurrentMap(const sead::SafeString& type, const sead::SafeString& name);
    static void setCurrentMapNameForFieldPos(const sead::Vector3f& pos);

    static void (*sChangeScene)(const sead::SafeString& map_name, const sead::SafeString& pos_name,
                                int x, bool triggered_by_stage_select);
    static bool sIsNotDebugStageAndNotDungeon;
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

private:
    static sead::FixedSafeString<32> sCurrentMapType;
    static sead::FixedSafeString<32> sCurrentMapName;
};

}  // namespace ksys
