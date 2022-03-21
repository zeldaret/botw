#include "agl/Utils/aglResParameter.h"
#include <basis/seadRawPrint.h>
#include <math/seadVector.h>
#include <prim/seadPtrUtil.h>
#include "agl/Utils/aglParameter.h"

namespace agl::utl {

size_t ResParameter::getDataSize() const {
    switch (ParameterType(ptr()->getType())) {
    case ParameterType::Bool:
    case ParameterType::F32:
    case ParameterType::Int:
    case ParameterType::U32:
        return 4;
    case ParameterType::Vec2:
        return sizeof(sead::Vector2f);
    case ParameterType::Vec3:
        return sizeof(sead::Vector3f);
    case ParameterType::Vec4:
    case ParameterType::Color:
    case ParameterType::Quat:
        return sizeof(sead::Vector4f);
    case ParameterType::String32:
    case ParameterType::String64:
    case ParameterType::String256:
    case ParameterType::StringRef:
        return sead::SafeString(getData<char>()).calcLength() + 1;
    case ParameterType::Curve1:
        return 1 * 0x80;
    case ParameterType::Curve2:
        return 2 * 0x80;
    case ParameterType::Curve3:
        return 3 * 0x80;
    case ParameterType::Curve4:
        return 4 * 0x80;
    case ParameterType::BufferInt:
    case ParameterType::BufferF32:
    case ParameterType::BufferU32:
        return 4 * getBufferSize();
    case ParameterType::BufferBinary:
        return getBufferSize();
    default:
        SEAD_ASSERT_MSG(false, "illigal type:%d", ptr()->getType());
        return 0;
    }
}

s32 ResParameterObj::searchIndex(u32 param_hash) const {
    for (s32 i = 0; i < getNum(); ++i) {
        if (getResParameter(i).getParameterNameHash() == param_hash)
            return i;
    }
    return -1;
}

s32 ResParameterList::searchListIndex(u32 list_hash) const {
    for (s32 i = 0; i < getResParameterListNum(); ++i) {
        if (getResParameterList(i).getParameterListNameHash() == list_hash)
            return i;
    }
    return -1;
}

s32 ResParameterList::searchObjIndex(u32 obj_hash) const {
    for (s32 i = 0; i < getResParameterObjNum(); ++i) {
        if (getResParameterObj(i).getParameterObjNameHash() == obj_hash)
            return i;
    }
    return -1;
}

// NON_MATCHING: partial implementation (unused conversion code is unimplemented)
ResParameterArchive::ResParameterArchive(const void* p_data) {
    mPtr = static_cast<ResParameterArchiveData*>(const_cast<void*>(p_data));
    if (!p_data)
        return;

    SEAD_ASSERT(sead::PtrUtil::isAlignedN(p_data, 4));
    if (mPtr->flags.isOff(ResParameterArchiveFlag::LittleEndian))
        ModifyEndianU32(false, mPtr, sizeof(ResParameterArchiveData));

    verify();

    if (mPtr->flags.isOn(ResParameterArchiveFlag::LittleEndian) &&
        mPtr->flags.isOn(ResParameterArchiveFlag::Utf8)) {
        // Nothing else to do.
        return;
    }

    // FIXME: implement endianness and string encoding conversion (requires PrivateResource)
    SEAD_ASSERT_MSG(false, "endianness and string conversion is unimplemented");
}

}  // namespace agl::utl
