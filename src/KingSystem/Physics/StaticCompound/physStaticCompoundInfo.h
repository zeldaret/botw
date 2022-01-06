#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkTypeInfo;

namespace ksys::phys {

struct ShapeInfo {
    HK_DECLARE_REFLECTION()

    hkInt32 m_ActorInfoIndex;
    hkInt32 m_InstanceId;
    hkInt8 m_BodyGroup;
    hkUint8 m_BodyLayerType;
};
extern const hkClass ShapeInfo_Class;
extern const hkTypeInfo ShapeInfo_TypeInfo;

struct ActorInfo {
    HK_DECLARE_REFLECTION()

    hkUint32 m_HashId;
    hkInt32 m_SRTHash;
    hkInt32 m_ShapeInfoStart;
    hkInt32 m_ShapeInfoEnd;
};
extern const hkClass ActorInfo_Class;
extern const hkTypeInfo ActorInfo_TypeInfo;

struct StaticCompoundInfo {
    HK_DECLARE_REFLECTION()

    hkUint32 m_Offset;
    hkArray<ActorInfo> m_ActorInfo;
    hkArray<ShapeInfo> m_ShapeInfo;
};
extern const hkClass StaticCompoundInfo_Class;
extern const hkTypeInfo StaticCompoundInfo_TypeInfo;

}  // namespace ksys::phys
