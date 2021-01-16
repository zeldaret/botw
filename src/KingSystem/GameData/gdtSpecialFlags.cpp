#include "KingSystem/GameData/gdtSpecialFlags.h"
#include <prim/seadStringUtil.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtFlagUtils.h"

namespace ksys::gdt {

const char* str_Dungeon = "Dungeon";
const char* str_Remains = "Remains";
const char* sSmallKeyNumFlagSuffix = "_SmallKeyNum";
const char* sDungeonClearFlagPrefix = "Clear_";
const char* sDungeonEnterFlagPrefix = "Enter_";

#define GDT_DEFINE_BOOL_GETTER(FLAG)                                                               \
    bool getBool_##FLAG(bool debug = false) { return getBool(flag_##FLAG(), debug); }

GDT_DEFINE_BOOL_GETTER(SaveProhibition)
GDT_DEFINE_BOOL_GETTER(SaveProhibitionArea)
GDT_DEFINE_BOOL_GETTER(WarpProhibition)
GDT_DEFINE_BOOL_GETTER(WarpProhibitionArea)
GDT_DEFINE_BOOL_GETTER(WarpProhibitionArea_Fire_Relic)
GDT_DEFINE_BOOL_GETTER(KillTimeProhibition)
GDT_DEFINE_BOOL_GETTER(KillTimeProhibitionArea)
GDT_DEFINE_BOOL_GETTER(KillTimeProhibitionArea_Fire_Relic)

#undef GDT_DEFINE_BOOL_GETTER

s32 getSmallKeyFlag(s32 idx, bool debug = false) {
    return getS32(flag_SmallKey(), idx, debug);
}

bool isSaveProhibited() {
    if (getBool_SaveProhibition())
        return true;
    if (getBool_SaveProhibitionArea())
        return true;
    return false;
}

bool isWarpProhibited() {
    if (getBool_WarpProhibition())
        return true;
    if (getBool_WarpProhibitionArea())
        return true;
    if (getBool_WarpProhibitionArea_Fire_Relic())
        return true;
    return false;
}

bool isKillTimeProhibited() {
    if (getBool_KillTimeProhibition())
        return true;
    if (getBool_KillTimeProhibitionArea())
        return true;
    if (getBool_KillTimeProhibitionArea_Fire_Relic())
        return true;
    return false;
}

s32 getSmallKeyNum(const sead::SafeString& map, bool debug) {
    if (map.startsWith(str_Remains)) {
        sead::FixedSafeString<32> flag{map};
        flag.append(sSmallKeyNumFlagSuffix);
        return getS32ByKey(flag, debug);
    }

    const s32 dungeon_num = getDungeonNum(map);
    if (dungeon_num == -1)
        return 0;

    return getSmallKeyFlag(dungeon_num, debug);
}

s32 getS32ByKey(const sead::SafeString& flag, bool debug) {
    s32 value{};

    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getS32(&value, flag);
        else
            mgr->getParam().get().getS32(&value, flag);
    }

    return value;
}

s32 getDungeonNum(const sead::SafeString& map) {
    if (map.startsWith(str_Dungeon)) {
        const sead::FixedSafeString<32> buffer{str_Dungeon};
        s32 ret = -1;

        const auto part = map.getPart(buffer.calcLength());
        if (sead::StringUtil::tryParseS32(&ret, part, sead::StringUtil::CardinalNumber::Base10))
            return ret;
    }
    return -1;
}

void incrementSmallKeyNum(const sead::SafeString& map, s32 value, bool debug) {
    if (map.startsWith(str_Remains)) {
        sead::FixedSafeString<32> flag{map};
        flag.append(sSmallKeyNumFlagSuffix);
        increaseS32CommonFlag(value, flag, -1, debug);
    } else {
        const s32 dungeon_number = getDungeonNum(map);
        if (dungeon_number != -1)
            increaseS32CommonFlag(value, "SmallKey", dungeon_number, debug);
    }
}

bool setS32ByKey(s32 value, const sead::SafeString& flag, bool debug) {
    auto* mgr = Manager::instance();
    return mgr && mgr->setS32Special(value, flag, debug, true);
}

bool setBoolByKey(bool value, const sead::SafeString& flag, bool debug) {
    auto* mgr = Manager::instance();
    return mgr && mgr->setBoolSpecial(value, flag, debug, true);
}

bool getBoolByKey(const sead::SafeString& flag, bool debug) {
    bool value{};

    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getBool(&value, flag);
        else
            mgr->getParam().get().getBool(&value, flag);
    }

    return value;
}

bool isDungeonCleared(const sead::SafeString& map, bool debug) {
    sead::FixedSafeString<32> flag{sDungeonClearFlagPrefix};
    flag.append(map, 32 - sizeof("Clear_"));
    return getBoolByKey(flag, debug);
}

void setDungeonCleared(const sead::SafeString& map, bool cleared, bool debug) {
    sead::FixedSafeString<32> flag{sDungeonClearFlagPrefix};
    flag.append(map, 32 - sizeof("Clear_"));
    setBoolByKey(cleared, flag, debug);
}

bool isDungeonEntered(const sead::SafeString& map, bool debug) {
    sead::FixedSafeString<32> flag{sDungeonEnterFlagPrefix};
    flag.append(map, 32 - sizeof("Enter_"));
    return getBoolByKey(flag, debug);
}

void setDungeonEntered(const sead::SafeString& map, bool cleared, bool debug) {
    sead::FixedSafeString<32> flag{sDungeonEnterFlagPrefix};
    flag.append(map, 32 - sizeof("Enter_"));
    setBoolByKey(cleared, flag, debug);
}

f32 getF32ByKey(const sead::SafeString& flag, bool debug) {
    f32 value{};

    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getF32(&value, flag);
        else
            mgr->getParam().get().getF32(&value, flag);
    }

    return value;
}

void getStr64ByKey(const char** value, const sead::SafeString& flag, bool debug) {
    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getStr64(value, flag);
        else
            mgr->getParam().get().getStr64(value, flag);
    }
}

void getVec3fByKey(sead::Vector3f* value, const sead::SafeString& flag, bool debug) {
    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getVec3f(value, flag);
        else
            mgr->getParam().get().getVec3f(value, flag);
    }
}

s32 getS32ByKey(const sead::SafeString& flag, s32 sub_idx, bool debug) {
    s32 value{};

    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getS32(&value, flag, sub_idx);
        else
            mgr->getParam().get().getS32(&value, flag, sub_idx);
    }

    return value;
}

f32 getF32ByKey(const sead::SafeString& flag, s32 sub_idx, bool debug) {
    f32 value{};

    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getF32(&value, flag, sub_idx);
        else
            mgr->getParam().get().getF32(&value, flag, sub_idx);
    }

    return value;
}

void getStr64ByKey(const char** value, const sead::SafeString& flag, s32 sub_idx, bool debug) {
    auto* mgr = Manager::instance();
    if (mgr) {
        if (debug)
            mgr->getParamBypassPerm().get().getStr64(value, flag, sub_idx);
        else
            mgr->getParam().get().getStr64(value, flag, sub_idx);
    }
}

bool setF32ByKey(f32 value, const sead::SafeString& flag, bool debug) {
    auto* mgr = Manager::instance();
    return mgr && mgr->setF32Special(value, flag, debug, true);
}

bool setStr64ByKey(const sead::SafeString& value, const sead::SafeString& flag, bool debug) {
    auto* mgr = Manager::instance();
    return mgr && mgr->setStr64Special(value, flag, debug, true);
}

}  // namespace ksys::gdt
