#include "KingSystem/System/StageInfo.h"

namespace ksys {

static sead::Atomic<int> sUnused;
void (*StageInfo::sChangeScene)(const sead::SafeString& map_name, const sead::SafeString& pos_name,
                                int x, bool triggered_by_stage_select);
bool StageInfo::sIsNotDebugStage;
bool StageInfo::sIsMainFieldDungeon;
bool StageInfo::sIsDungeon;
bool StageInfo::sIsCDungeon;
bool StageInfo::sIsMainFieldDungeon2;
bool StageInfo::sIsActorViewer;
bool StageInfo::sIsStageDebug;
bool StageInfo::sIsTestDungeon;
bool StageInfo::sIsDebugOrDevMap;
bool StageInfo::sIsRemainsElectric;
bool StageInfo::sIsRemainsFire;
bool StageInfo::sIsRemainsWater;
bool StageInfo::sIsRemainsWind;
bool StageInfo::sIsFinalTrial;
bool StageInfo::sIsAocField;
bool StageInfo::sIsMainField;
sead::FixedSafeString<32> StageInfo::sCurrentMapType;
sead::FixedSafeString<32> StageInfo::sCurrentMapName;

}  // namespace ksys
