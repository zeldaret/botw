#include "agl/Utils/aglParameter.h"
#include <codec/seadHashCRC32.h>
#include <gfx/seadColor.h>
#include <math/seadQuatCalcCommon.h>
#include <math/seadVector.h>
#include <prim/seadFormatPrint.h>
#include <prim/seadMemUtil.h>
#include "agl/Utils/aglParameterObj.h"
#include "agl/Utils/aglParameterStringMgr.h"

namespace agl::utl {

static constexpr const char* sParameterTypeNames[] = {
    "bool",       "f32",       "int",    "vec2",   "vec3",       "vec4",          "color",
    "string32",   "string64",  "curve1", "curve2", "curve3",     "curve4",        "buffer_int",
    "buffer_f32", "string256", "quat",   "u32",    "buffer_u32", "buffer_binary", "stringRef",
};

u32 ParameterBase::calcHash(const sead::SafeString& key) {
    return sead::HashCRC32::calcStringHash(key);
}

ParameterBase::ParameterBase() {
    initializeListNode("default", "parameter", "", nullptr);
}

ParameterBase::ParameterBase(const sead::SafeString& name, const sead::SafeString& label,
                             IParameterObj* param_obj) {
    initializeListNode(name, label, "", param_obj);
}

ParameterBase::ParameterBase(const sead::SafeString& name, const sead::SafeString& label,
                             const sead::SafeString& meta, IParameterObj* param_obj) {
    initializeListNode(name, label, meta, param_obj);
}

void ParameterBase::initializeListNode(const sead::SafeString& name, const sead::SafeString& label,
                                       const sead::SafeString& meta, IParameterObj* param_obj) {
    mNext = nullptr;

#ifdef SEAD_DEBUG
    if (ParameterStringMgr::instance()) {
        mName = ParameterStringMgr::instance()->appendString(name);
        mLabel = ParameterStringMgr::instance()->appendString(label);
        mMeta = ParameterStringMgr::instance()->appendString(meta);
    } else {
        mName = nullptr;
        mLabel = nullptr;
        mMeta = nullptr;
    }
#endif

    mNameHash = calcHash(name);

    if (param_obj)
        param_obj->pushBackListNode(this);
}

sead::SafeString ParameterBase::getParameterName() const {
#ifdef SEAD_DEBUG
    return mName;
#else
    return sead::SafeString::cEmptyString;
#endif
}

sead::SafeString ParameterBase::getLabel() const {
#ifdef SEAD_DEBUG
    return mLabel;
#else
    return sead::SafeString::cEmptyString;
#endif
}

sead::SafeString ParameterBase::getMeta() const {
#ifdef SEAD_DEBUG
    return mMeta;
#else
    return sead::SafeString::cEmptyString;
#endif
}

const char* ParameterBase::getTagName() {
    return "param";
}

const char* ParameterBase::getAttributeNameString() {
    return "name";
}

const char* ParameterBase::getAttributeTypeString() {
    return "type";
}

const char* ParameterBase::getAttributeValueString() {
    return "value";
}

const char* ParameterBase::getParameterTypeName(ParameterType type) {
    return sParameterTypeNames[u32(type)];
}

// NON_MATCHING: Clang emits a switch...
bool ParameterBase::isSafeType(ParameterType type) const {
    if (getParameterType() == type)
        return true;

    constexpr std::pair<ParameterType, ParameterType> pairs[] = {
        {ParameterType::String64, ParameterType::String32},
        {ParameterType::String32, ParameterType::String64},
        {ParameterType::String256, ParameterType::String32},
        {ParameterType::String256, ParameterType::String64},
        {ParameterType::String32, ParameterType::String256},
        {ParameterType::String64, ParameterType::String256},
    };

    for (const auto pair : pairs) {
        if (type == pair.first && getParameterType() == pair.second)
            return true;
    }

    if (getParameterType() == ParameterType::StringRef &&
        (type == ParameterType::String32 || type == ParameterType::String64 ||
         type == ParameterType::String256)) {
        return true;
    }

    return false;
}

bool ParameterBase::verifyType(ParameterType type) const {
    if (isSafeType(type))
        return true;

    sead::BufferingPrintFormatter ss;
    ss << "!!! AGL ERROR !!! Instance ParameterType = %s Resource ParameterType = %s\n"
       << sParameterTypeNames[u32(getParameterType())] << sParameterTypeNames[u32(type)]
       << sead::flush;
    return false;
}

bool ParameterBase::copy(const ParameterBase& other) {
    if (getParameterType() != other.getParameterType() || mNameHash != other.mNameHash)
        return false;

    copyUnsafe(other);
    return true;
}

void ParameterBase::copyUnsafe(const ParameterBase& other) {
    if (other.getParameterType() == ParameterType::StringRef) {
        auto* source = static_cast<const sead::SafeString*>(other.typePtr());
        auto* dest = static_cast<sead::SafeString*>(typePtr());
        *dest = *source;
        return;
    }

    auto* dest = ptrT<u8>();
    auto* src = other.ptrT<u8>();
    const s32 n = size();
    for (s32 i = 0; i < n; ++i)
        *dest++ = *src++;
}

template <>
void ParameterBase::copyLerp_<f32>(const ParameterBase& param1, const ParameterBase& param2,
                                   f32 t) {
    *ptrT<f32>() = sead::lerp(*param1.ptrT<f32>(), *param2.ptrT<f32>(), t);
}

template <>
void ParameterBase::copyLerp_<sead::Quatf>(const ParameterBase& param1, const ParameterBase& param2,
                                           f32 t) {
    sead::QuatCalcCommon<f32>::slerpTo(*ptrT<sead::Quatf>(), *param1.ptrT<sead::Quatf>(),
                                       *param2.ptrT<sead::Quatf>(), t);
}

template <typename T>
static void lerpVec_(T& v_dest, const T& v1, const T& v2, f32 t) {
    for (size_t i = 0; i < v_dest.e.size(); ++i)
        v_dest.e[i] = sead::lerp(v1.e[i], v2.e[i], t);
}

template <typename T>
static void copyLerpVec_(ParameterBase& dest, const ParameterBase& param1,
                         const ParameterBase& param2, f32 t) {
    lerpVec_(*dest.ptrT<T>(), *param1.ptrT<T>(), *param2.ptrT<T>(), t);
}

bool ParameterBase::copyLerp(const ParameterBase& param1, const ParameterBase& param2, f32 t) {
    if (getParameterType() != param1.getParameterType() || mNameHash != param1.mNameHash)
        return false;

    if (getParameterType() != param2.getParameterType() || mNameHash != param2.mNameHash)
        return false;

    switch (getParameterType()) {
    case ParameterType::Bool:
    case ParameterType::Int:
    case ParameterType::String32:
    case ParameterType::String64:
    case ParameterType::String256:
    case ParameterType::U32:
        copyUnsafe(param1);
        return true;
    case ParameterType::F32:
        copyLerp_<f32>(param1, param2, t);
        return true;
    case ParameterType::Vec2:
        copyLerpVec_<sead::Vector2f>(*this, param1, param2, t);
        return true;
    case ParameterType::Vec3:
        copyLerpVec_<sead::Vector3f>(*this, param1, param2, t);
        return true;
    case ParameterType::Vec4:
        copyLerpVec_<sead::Vector4f>(*this, param1, param2, t);
        return true;
    case ParameterType::Color: {
        auto& color = *ptrT<sead::Color4f>();
        color.setLerp(*param1.ptrT<sead::Color4f>(), *param2.ptrT<sead::Color4f>(), t);
        return true;
    }
    case ParameterType::Curve1:
    case ParameterType::Curve2:
    case ParameterType::Curve3:
    case ParameterType::Curve4:
    case ParameterType::BufferInt:
    case ParameterType::BufferF32:
    case ParameterType::BufferU32:
    case ParameterType::BufferBinary:
    case ParameterType::StringRef:
    case ParameterType::Special:
        return true;
    case ParameterType::Quat:
        copyLerp_<sead::Quatf>(param1, param2, t);
        return true;
    default:
        SEAD_ASSERT_MSG(false, "%d", int(getParameterType()));
        return true;
    }
}

static void applyResourceSimple_(ParameterBase& param, const ResParameter& res) {
    void* dest = param.ptr();
    const void* src = res.getData<void>();

    const size_t data_size = param.size();
    const size_t res_data_size = res.getDataSize();
    const auto copy_size = data_size < res_data_size ? data_size : res_data_size;

    sead::MemUtil::copy(dest, src, copy_size);
}

void ParameterBase::applyResource(ResParameter res) {
#ifdef SEAD_DEBUG
    if (!verifyType(ParameterType(res.ptr()->getType())))
        return;
#endif

    if (getParameterType() == ParameterType::Bool) {
        const bool value = *res.getData<u32>() != 0;
        *ptrT<bool>() = value;
    } else if (isBinaryInternalBuffer()) {
        if (getParameterType() == ParameterType::StringRef)
            *static_cast<sead::SafeString*>(typePtr()) = res.getData<char>();
        else
            applyResourceSimple_(*this, res);
    }

    postApplyResource_(res.getData<void>(), res.getDataSize());
}

void ParameterBase::applyResource(ResParameter res, f32 t) {
#ifdef SEAD_DEBUG
    if (!verifyType(ParameterType(res.ptr()->getType())))
        return;
#endif

    switch (getParameterType()) {
    case ParameterType::Bool:
        *ptrT<bool>() = *res.getData<u32>() != 0;
        break;
    case ParameterType::F32: {
        f32 x;
        sead::MemUtil::copy(&x, res.getData<void>(), size());
        *ptrT<f32>() += x * t;
        break;
    }
    case ParameterType::Int:
    case ParameterType::String32:
    case ParameterType::String64:
    case ParameterType::String256:
    case ParameterType::U32:
        applyResourceSimple_(*this, res);
        break;
    case ParameterType::Vec2: {
        sead::Vector2f vec;
        sead::MemUtil::copy(&vec, res.getData<void>(), size());
        *ptrT<sead::Vector2f>() += vec * t;
        break;
    }
    case ParameterType::Vec3: {
        sead::Vector3f vec;
        sead::MemUtil::copy(&vec, res.getData<void>(), size());
        *ptrT<sead::Vector3f>() += vec * t;
        break;
    }
    case ParameterType::Vec4: {
        sead::Vector4f vec;
        sead::MemUtil::copy(&vec, res.getData<void>(), size());
        *ptrT<sead::Vector4f>() += vec * t;
        break;
    }
    case ParameterType::Color: {
        sead::Color4f color;
        sead::MemUtil::copy(&color, res.getData<void>(), size());
        *ptrT<sead::Color4f>() += color * sead::Color4f{t, t, t, t};
        break;
    }
    case ParameterType::Curve1:
    case ParameterType::Curve2:
    case ParameterType::Curve3:
    case ParameterType::Curve4:
    case ParameterType::Special:
        break;
    case ParameterType::BufferInt:
    case ParameterType::BufferF32:
    case ParameterType::BufferU32:
    case ParameterType::BufferBinary:
        if (isBinaryInternalBuffer())
            applyResourceSimple_(*this, res);
        break;
    case ParameterType::Quat: {
        sead::Quatf quat;
        sead::MemUtil::copy(&quat, res.getData<void>(), size());
        auto* target = ptrT<sead::Quatf>();
        sead::QuatCalcCommon<f32>::slerpTo(*target, *target, quat, t);
        break;
    }
    case ParameterType::StringRef:
        *static_cast<sead::SafeString*>(typePtr()) = res.getData<char>();
        break;
    default:
        SEAD_ASSERT_MSG(false, "%d", int(getParameterType()));
        break;
    }

    postApplyResource_(res.getData<void>(), res.getDataSize());
}

bool ParameterBase::isInterpolatable() const {
    const auto type = getParameterType();
    return type == ParameterType::F32 || type == ParameterType::Vec2 ||
           type == ParameterType::Vec3 || type == ParameterType::Vec4 ||
           type == ParameterType::Color || type == ParameterType::Quat;
}

size_t ParameterBase::binarize(void* binary) const {
    SEAD_ASSERT(binary != nullptr);

    size_t binary_size;
    if (getParameterType() != ParameterType::Bool) {
        binary_size = calcBinarizeSize();
        sead::MemUtil::copy(binary, ptr(), binary_size);
    } else {
        binary_size = sizeof(u32);
        *static_cast<u32*>(binary) = *ptrT<bool>();
    }
    return binary_size;
}

bool ParameterBase::makeZero() {
    switch (getParameterType()) {
    case ParameterType::F32:
        *ptrT<f32>() = 0;
        return true;
    case ParameterType::Vec2:
        *ptrT<sead::Vector2f>() = {0, 0};
        return true;
    case ParameterType::Vec3:
        *ptrT<sead::Vector3f>() = {0, 0, 0};
        return true;
    case ParameterType::Vec4:
        *ptrT<sead::Vector4f>() = {0, 0, 0, 0};
        return true;
    case ParameterType::Color:
        *ptrT<sead::Color4f>() = {0, 0, 0, 0};
        return true;
    case ParameterType::Quat: {
        auto* quat = ptrT<sead::Quatf>();
        quat->z = 0;
        quat->w = 1;
        quat->x = quat->y = 0;
        return true;
    }
    case ParameterType::Bool:
    case ParameterType::Int:
    case ParameterType::String32:
    case ParameterType::String64:
    case ParameterType::Curve1:
    case ParameterType::Curve2:
    case ParameterType::Curve3:
    case ParameterType::Curve4:
    case ParameterType::BufferInt:
    case ParameterType::BufferF32:
    case ParameterType::String256:
    case ParameterType::U32:
    case ParameterType::BufferU32:
    case ParameterType::BufferBinary:
    case ParameterType::StringRef:
    case ParameterType::Special:
        return false;
    }
    return false;
}

// TODO: Remove these explicit instantiations once ParameterBase::createByTypeName is implemented.
template class Parameter<bool>;
template class Parameter<f32>;
template class Parameter<s32>;
template class Parameter<sead::Vector2f>;
template class Parameter<sead::Vector3f>;
template class Parameter<sead::Vector4f>;
template class Parameter<sead::Color4f>;
template class Parameter<sead::FixedSafeString<32>>;
template class Parameter<sead::FixedSafeString<64>>;
template class Parameter<sead::FixedSafeString<256>>;
template class Parameter<sead::Quatf>;
template class Parameter<u32>;
template class Parameter<sead::SafeString>;
template class ParameterCurve<1>;
template class ParameterCurve<2>;
template class ParameterCurve<3>;
template class ParameterCurve<4>;

}  // namespace agl::utl
