#include "KingSystem/Map/mapMubinIter.h"
#include <codec/seadHashCRC32.h>

namespace ksys::map {

namespace {
struct KeyHashes {
    KeyHashes() {
        SRTHash = sead::HashCRC32::calcStringHash("SRTHash");
        Index = sead::HashCRC32::calcStringHash("Index");
        HashId = sead::HashCRC32::calcStringHash("HashId");
        DestUnitHashId = sead::HashCRC32::calcStringHash("DestUnitHashId");
        LocationPosX = sead::HashCRC32::calcStringHash("LocationPosX");
        LocationPosZ = sead::HashCRC32::calcStringHash("LocationPosZ");
        NextDistance = sead::HashCRC32::calcStringHash("NextDistance");
        PrevDistance = sead::HashCRC32::calcStringHash("PrevDistance");
        IsClosed = sead::HashCRC32::calcStringHash("IsClosed");
        OnlyOne = sead::HashCRC32::calcStringHash("OnlyOne");
        RailType = sead::HashCRC32::calcStringHash("RailType");
        UniqueName = sead::HashCRC32::calcStringHash("UniqueName");
        UnitConfigName = sead::HashCRC32::calcStringHash("UnitConfigName");
        CheckPointName = sead::HashCRC32::calcStringHash("CheckPointName");
        EntryPointName = sead::HashCRC32::calcStringHash("EntryPointName");
        DefinitionName = sead::HashCRC32::calcStringHash("DefinitionName");
        Objs = sead::HashCRC32::calcStringHash("Objs");
        Rails = sead::HashCRC32::calcStringHash("Rails");
        LinksToObj = sead::HashCRC32::calcStringHash("LinksToObj");
        LinksToRail = sead::HashCRC32::calcStringHash("LinksToRail");
        Rotate = sead::HashCRC32::calcStringHash("Rotate");
        Scale = sead::HashCRC32::calcStringHash("Scale");
        Translate = sead::HashCRC32::calcStringHash("Translate");
        RailPoints = sead::HashCRC32::calcStringHash("RailPoints");
        ControlPoints = sead::HashCRC32::calcStringHash("ControlPoints");
        Junctions = sead::HashCRC32::calcStringHash("Junctions");
    }

    u32 SRTHash;
    u32 Index;
    u32 HashId;
    u32 DestUnitHashId;
    u32 IsClosed;
    u32 OnlyOne;
    u32 LocationPosX;
    u32 LocationPosZ;
    u32 NextDistance;
    u32 PrevDistance;
    u32 RailType;
    u32 UniqueName;
    u32 UnitConfigName;
    u32 CheckPointName;
    u32 EntryPointName;
    u32 DefinitionName;
    u32 Objs;
    u32 Rails;
    u32 LinksToObj;
    u32 LinksToRail;
    u32 Rotate;
    u32 Scale;
    u32 Translate;
    u32 RailPoints;
    u32 ControlPoints;
    u32 Junctions;
};
const KeyHashes sHashes;
}  // namespace

MubinIter::MubinIter() : ByamlIter() {}

MubinIter::MubinIter(const u8* data) : ByamlIter(data) {}

bool MubinIter::tryGetParamUInt8ByKey(u8* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key);

    if (sHashes.SRTHash == hash || sHashes.Index == hash) {
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
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.SRTHash == hash || sHashes.Index == hash)
        return tryGetIntByKey(value, key.cstr());

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetIntByKey(value, key.cstr());
}

bool MubinIter::tryGetParamUIntByKey(u32* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.HashId == hash || sHashes.DestUnitHashId == hash)
        return tryGetUIntByKey(value, key.cstr());

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetUIntByKey(value, key.cstr());
}

bool MubinIter::tryGetParamFloatByKey(f32* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.LocationPosX == hash || sHashes.LocationPosZ == hash ||
        sHashes.NextDistance == hash || sHashes.PrevDistance == hash) {
        return tryGetFloatByKey(value, key.cstr());
    }

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetFloatByKey(value, key.cstr());
}

bool MubinIter::tryGetParamBoolByKey(bool* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.IsClosed == hash || sHashes.OnlyOne == hash)
        return tryGetBoolByKey(value, key.cstr());

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetBoolByKey(value, key.cstr());
}

bool MubinIter::tryGetParamStringByKey(const char** value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.RailType == hash || sHashes.UniqueName == hash || sHashes.UnitConfigName == hash ||
        sHashes.CheckPointName == hash || sHashes.EntryPointName == hash ||
        sHashes.DefinitionName == hash) {
        return tryGetStringByKey(value, key.cstr());
    }

    al::ByamlIter iter;
    return tryGetIterByIndex(&iter, 0) && iter.tryGetStringByKey(value, key.cstr());
}

bool MubinIter::tryGetIterByIndex(MubinIter* iter, s32 index) const {
    return al::ByamlIter::tryGetIterByIndex(iter, index);
}

bool MubinIter::tryGetParamIterByKey(MubinIter* value, const sead::SafeString& key) const {
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.Objs == hash || sHashes.Rails == hash || sHashes.LinksToObj == hash ||
        sHashes.LinksToRail == hash || sHashes.Rotate == hash || sHashes.Scale == hash ||
        sHashes.Translate == hash || sHashes.RailPoints == hash || sHashes.ControlPoints == hash ||
        sHashes.Junctions == hash) {
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
    const u32 hash = sead::HashCRC32::calcStringHash(key);
    if (sHashes.Objs == hash || sHashes.Rails == hash || sHashes.LinksToObj == hash ||
        sHashes.LinksToRail == hash || sHashes.Rotate == hash || sHashes.Scale == hash ||
        sHashes.Translate == hash || sHashes.RailPoints == hash || sHashes.ControlPoints == hash ||
        sHashes.Junctions == hash) {
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
