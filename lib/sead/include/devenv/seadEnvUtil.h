#pragma once

#include "prim/seadEnum.h"
#include "prim/seadSafeString.h"

namespace sead
{
SEAD_ENUM(RegionLanguageID, JPja, USen, USes, USfr, USpt, EUen, EUes, EUfr, EUde, EUit, EUpt, EUnl, EUru, KRko, CNzh, TWzh)

class EnvUtil
{
public:
    static const SafeString& getRomType();
    static RegionLanguageID getRegionLanguage();
    static s32 getEnvironmentVariable(BufferedSafeString* out, const SafeString& variable);
    static s32 resolveEnvronmentVariable(BufferedSafeString* out, const SafeString& str);
};
}  // namespace sead
