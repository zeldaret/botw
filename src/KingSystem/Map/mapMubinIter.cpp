#include "KingSystem/Map/mapMubinIter.h"
#include <codec/seadHashCRC32.h>

namespace ksys::map {

static const u32 sCrc32_SRTHash = sead::HashCRC32::calcStringHash("SRTHash");
static const u32 sCrc32_Index = sead::HashCRC32::calcStringHash("Index");
static const u32 sCrc32_HashId = sead::HashCRC32::calcStringHash("HashId");
static const u32 sCrc32_DestUnitHashId = sead::HashCRC32::calcStringHash("DestUnitHashId");
static const u32 sCrc32_LocationPosX = sead::HashCRC32::calcStringHash("LocationPosX");
static const u32 sCrc32_LocationPosZ = sead::HashCRC32::calcStringHash("LocationPosZ");
static const u32 sCrc32_NextDistance = sead::HashCRC32::calcStringHash("NextDistance");
static const u32 sCrc32_PrevDistance = sead::HashCRC32::calcStringHash("PrevDistance");
static const u32 sCrc32_IsClosed = sead::HashCRC32::calcStringHash("IsClosed");
static const u32 sCrc32_OnlyOne = sead::HashCRC32::calcStringHash("OnlyOne");
static const u32 sCrc32_RailType = sead::HashCRC32::calcStringHash("RailType");
static const u32 sCrc32_UniqueName = sead::HashCRC32::calcStringHash("UniqueName");
static const u32 sCrc32_UnitConfigName = sead::HashCRC32::calcStringHash("UnitConfigName");
static const u32 sCrc32_CheckPointName = sead::HashCRC32::calcStringHash("CheckPointName");
static const u32 sCrc32_EntryPointName = sead::HashCRC32::calcStringHash("EntryPointName");
static const u32 sCrc32_DefinitionName = sead::HashCRC32::calcStringHash("DefinitionName");
static const u32 sCrc32_Objs = sead::HashCRC32::calcStringHash("Objs");
static const u32 sCrc32_Rails = sead::HashCRC32::calcStringHash("Rails");
static const u32 sCrc32_LinksToObj = sead::HashCRC32::calcStringHash("LinksToObj");
static const u32 sCrc32_LinksToRail = sead::HashCRC32::calcStringHash("LinksToRail");
static const u32 sCrc32_Rotate = sead::HashCRC32::calcStringHash("Rotate");
static const u32 sCrc32_Scale = sead::HashCRC32::calcStringHash("Scale");
static const u32 sCrc32_Translate = sead::HashCRC32::calcStringHash("Translate");
static const u32 sCrc32_RailPoints = sead::HashCRC32::calcStringHash("RailPoints");
static const u32 sCrc32_ControlPoints = sead::HashCRC32::calcStringHash("ControlPoints");
static const u32 sCrc32_Junctions = sead::HashCRC32::calcStringHash("Junctions");

MubinIter::MubinIter() : ByamlIter() {}

MubinIter::MubinIter(const u8* data) : ByamlIter(data) {}

bool MubinIter::tryGetParamUInt8ByKey(u8* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());

    if (sCrc32_SRTHash == hash || sCrc32_Index == hash) {
        s32 x = 0;
        if (!tryGetIntByKey(&x, key.cstr()))
            return false;
        *value = x;
        return true;
    }

    al::ByamlIter iter;
    if (!tryGetIterByIndex(&iter, 0))
        return false;
    s32 x = 0;
    if (!iter.tryGetIntByKey(&x, key.cstr()))
        return false;
    *value = x;
    return true;
}

bool MubinIter::tryGetParamIntByKey(s32* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_SRTHash == hash || sCrc32_Index == hash)
        return tryGetIntByKey(value, key.cstr());

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetIntByKey(value, key.cstr());
}

bool MubinIter::tryGetParamUIntByKey(u32* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_HashId == hash || sCrc32_DestUnitHashId == hash)
        return tryGetUIntByKey(value, key.cstr());

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetUIntByKey(value, key.cstr());
}

bool MubinIter::tryGetParamFloatByKey(f32* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_LocationPosX == hash || sCrc32_LocationPosZ == hash || sCrc32_NextDistance == hash ||
        sCrc32_PrevDistance == hash) {
        return tryGetFloatByKey(value, key.cstr());
    }

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetFloatByKey(value, key.cstr());
}

bool MubinIter::tryGetParamBoolByKey(bool* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_IsClosed == hash || sCrc32_OnlyOne == hash)
        return tryGetBoolByKey(value, key.cstr());

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetBoolByKey(value, key.cstr());
}

bool MubinIter::tryGetParamStringByKey(const char** value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_RailType == hash || sCrc32_UniqueName == hash || sCrc32_UnitConfigName == hash ||
        sCrc32_CheckPointName == hash || sCrc32_EntryPointName == hash ||
        sCrc32_DefinitionName == hash) {
        return tryGetStringByKey(value, key.cstr());
    }

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetStringByKey(value, key.cstr());
}

bool MubinIter::tryGetIterByIndex(MubinIter* iter, s32 index) const {
    return al::ByamlIter::tryGetIterByIndex(iter, index);
}

bool MubinIter::tryGetParamIterByKey(MubinIter* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_Objs == hash || sCrc32_Rails == hash || sCrc32_LinksToObj == hash ||
        sCrc32_LinksToRail == hash || sCrc32_Rotate == hash || sCrc32_Scale == hash ||
        sCrc32_Translate == hash || sCrc32_RailPoints == hash || sCrc32_ControlPoints == hash ||
        sCrc32_Junctions == hash) {
        return tryGetIterByKey(value, key.cstr());
    }

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetIterByKey(value, key.cstr());
}

s32 MubinIter::getSize() const {
    return al::ByamlIter::getSize();
}

bool MubinIter::isValid() const {
    return al::ByamlIter::isValid();
}

bool MubinIter::tryGetFloatArrayByKey(f32* value, const sead::SafeString& key) const {
    al::ByamlIter iter;
    const u32 hash = sead::HashCRC32::calcStringHash(key.cstr());
    if (sCrc32_Objs == hash || sCrc32_Rails == hash || sCrc32_LinksToObj == hash ||
        sCrc32_LinksToRail == hash || sCrc32_Rotate == hash || sCrc32_Scale == hash ||
        sCrc32_Translate == hash || sCrc32_RailPoints == hash || sCrc32_ControlPoints == hash ||
        sCrc32_Junctions == hash) {
        if (!tryGetIterByKey(&iter, key.cstr()))
            return false;
    } else {
        al::ByamlIter i;
        if (!tryGetIterByIndex(&i, 0) || !i.tryGetIterByKey(&iter, key.cstr()))
            return false;
    }

    const s32 size = iter.getSize();
    bool ok = true;
    for (s32 i = 0; i < size; ++i) {
        ok &= iter.tryGetFloatByIndex(&value[i], i);
    }
    return ok;
}

bool MubinIter::tryGetControlPoints(ControlPoints* points) const {
    al::ByamlIter pts_iter;
    if (!tryGetIterByKey(&pts_iter, "ControlPoints")) {
        *points = {};
        return false;
    }

    const s32 num_pts = pts_iter.getSize();

    for (s32 pt_idx = 0; pt_idx < num_pts; ++pt_idx) {
        al::ByamlIter iter;
        if (!pts_iter.tryGetIterByIndex(&iter, pt_idx))
            return false;

        const s32 num_coords = iter.getSize();
        for (s32 i = 0; i < num_coords; ++i) {
            if (!iter.tryGetFloatByIndex(&(*points)[pt_idx].e[i], i))
                return false;
        }
    }

    return true;
}

void MubinIter::getSRT(SRT* srt) const {
    getScale(&srt->scale);
    getRotate(&srt->rotate);
    getTranslate(&srt->translate);
}

void MubinIter::getScale(sead::Vector3f* scale) const {
    al::ByamlIter iter;
    if (tryGetIterByKey(&iter, "Scale")) {
        for (s32 i = 0, n = iter.getSize(); i < n; ++i) {
            if (!iter.tryGetFloatByIndex(&scale->e[i], i))
                scale->e[i] = 1.0;
        }
    } else if (tryGetFloatByKey(&scale->e[0], "Scale")) {
        scale->e[1] = scale->e[2] = scale->e[0];
    } else {
        *scale = sead::Vector3f::ones;
    }
}

void MubinIter::getRotate(sead::Vector3f* rotate) const {
    al::ByamlIter iter;
    if (tryGetIterByKey(&iter, "Rotate")) {
        for (s32 i = 0, n = iter.getSize(); i < n; ++i) {
            if (!iter.tryGetFloatByIndex(&rotate->e[i], i))
                rotate->e[i] = 0.0;
        }
    } else {
        rotate->x = rotate->z = 0.0;
        if (!tryGetFloatByKey(&rotate->y, "Rotate"))
            rotate->y = 0.0;
    }
}

void MubinIter::getTranslate(sead::Vector3f* translate) const {
    tryGetFloatArrayByKey(translate->e.data(), "Translate");
}

}  // namespace ksys::map
