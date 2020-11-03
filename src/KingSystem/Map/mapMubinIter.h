#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Map/mapTypes.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::map {

struct SRT;

class MubinIter : public al::ByamlIter {
public:
    MubinIter();
    explicit MubinIter(const u8* data);

    bool tryGetParamUInt8ByKey(u8* value, const sead::SafeString& key) const;
    bool tryGetParamIntByKey(s32* value, const sead::SafeString& key) const;
    bool tryGetParamUIntByKey(u32* value, const sead::SafeString& key) const;
    bool tryGetParamFloatByKey(f32* value, const sead::SafeString& key) const;
    bool tryGetParamBoolByKey(bool* value, const sead::SafeString& key) const;
    bool tryGetParamStringByKey(const char** value, const sead::SafeString& key) const;
    bool tryGetIterByIndex(MubinIter* iter, s32 index) const;
    using al::ByamlIter::tryGetIterByIndex;
    bool tryGetParamIterByKey(MubinIter* value, const sead::SafeString& key) const;
    using al::ByamlIter::tryGetIterByKey;

    s32 getSize() const;
    bool isValid() const;

    /// @warning UNSAFE. Will happily write as many floats as there are items in the BYML data.
    bool tryGetFloatArrayByKey(f32* array, const sead::SafeString& key) const;

    /// @warning UNSAFE. Will happily write as many floats as there are items in the BYML data.
    bool tryGetControlPoints(ControlPoints* points) const;

    /// @warning UNSAFE. Will happily write as many floats as there are items in the BYML data.
    void getSRT(SRT* srt) const;

    /// @warning UNSAFE. Will happily write as many floats as there are items in the BYML data.
    void getScale(sead::Vector3f* scale) const;

    /// @warning UNSAFE. Will happily write as many floats as there are items in the BYML data.
    void getRotate(sead::Vector3f* rotate) const;

    /// @warning UNSAFE. Will happily write as many floats as there are items in the BYML data.
    void getTranslate(sead::Vector3f* translate) const;
};

}  // namespace ksys::map
