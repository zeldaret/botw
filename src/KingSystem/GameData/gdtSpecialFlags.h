#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

namespace ksys::gdt {

bool isSaveProhibited();
bool isWarpProhibited();
bool isKillTimeProhibited();

s32 getSmallKeyNum(const sead::SafeString& map, bool debug = false);
s32 getDungeonNum(const sead::SafeString& map);
void incrementSmallKeyNum(const sead::SafeString& map, s32 value, bool debug = false);

s32 getS32ByKey(const sead::SafeString& flag, bool debug = false);
bool setS32ByKey(s32 value, const sead::SafeString& flag, bool debug = false);

bool setBoolByKey(bool value, const sead::SafeString& flag, bool debug = false);
bool getBoolByKey(const sead::SafeString& flag, bool debug = false);

bool isDungeonCleared(const sead::SafeString& map, bool debug = false);
void setDungeonCleared(const sead::SafeString& map, bool cleared, bool debug = false);

bool isDungeonEntered(const sead::SafeString& map, bool debug = false);
void setDungeonEntered(const sead::SafeString& map, bool entered, bool debug = false);

bool isGetItem(const sead::SafeString& actor, bool debug = false);
bool isGetItem(act::Actor* actor, bool debug = false);
void setIsGetItem(const sead::SafeString& actor, bool value, bool debug = false);
// XXX: Same as isGetItem -- why does this exist?
bool isGetItem2(const sead::SafeString& actor, bool debug = false);
void setIsGetItem2(const sead::SafeString& actor, bool value, bool debug = false);

f32 getF32ByKey(const sead::SafeString& flag, bool debug = false);
void getStr64ByKey(const char** value, const sead::SafeString& flag, bool debug = false);
void getVec3fByKey(sead::Vector3f* value, const sead::SafeString& flag, bool debug = false);
s32 getS32ByKey(const sead::SafeString& flag, s32 sub_idx, bool debug = false);
f32 getF32ByKey(const sead::SafeString& flag, s32 sub_idx, bool debug = false);
void getStr64ByKey(const char** value, const sead::SafeString& flag, s32 sub_idx,
                   bool debug = false);
bool setF32ByKey(f32 value, const sead::SafeString& flag, bool debug = false);
bool setStr64ByKey(const sead::SafeString& value, const sead::SafeString& flag, bool debug = false);

}  // namespace ksys::gdt
