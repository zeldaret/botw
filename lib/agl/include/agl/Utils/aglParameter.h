#pragma once

#include <array>
#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <hostio/seadHostIOCurve.h>
#include <hostio/seadHostIOReflexible.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <type_traits>
#include "agl/Utils/aglResParameter.h"

namespace sead {
class Heap;
class XmlElement;
}  // namespace sead

namespace agl::utl {

class IParameterObj;

class ParameterBase {
public:
    enum class ParameterType {
        Bool = 0,
        F32 = 1,
        Int = 2,
        Vec2 = 3,
        Vec3 = 4,
        Vec4 = 5,
        Color = 6,
        String32 = 7,
        String64 = 8,
        Curve1 = 9,
        Curve2 = 10,
        Curve3 = 11,
        Curve4 = 12,
        BufferInt = 13,
        BufferF32 = 14,
        String256 = 15,
        Quat = 16,
        U32 = 17,
        BufferU32 = 18,
        BufferBinary = 19,
        StringRef = 20,
        Special = 21,
    };

    ParameterBase();
    ParameterBase(const sead::SafeString& name, const sead::SafeString& label,
                  IParameterObj* param_obj);
    ParameterBase(const sead::SafeString& name, const sead::SafeString& label,
                  const sead::SafeString& meta, IParameterObj* param_obj);
    virtual ~ParameterBase() { ; }

    void initializeListNode(const sead::SafeString& name, const sead::SafeString& label,
                            const sead::SafeString& meta, IParameterObj* param_obj);

    u32 getNameHash() const { return mNameHash; }
    sead::SafeString getParameterName() const;
    sead::SafeString getName() const { return getParameterName(); }
    sead::SafeString getLabel() const;
    sead::SafeString getMeta() const;

    ParameterBase* getNext() const { return mNext; }

    static const char* getTagName();
    static const char* getAttributeNameString();
    static const char* getAttributeTypeString();
    static const char* getAttributeValueString();
    static const char* getParameterTypeName(ParameterType type);

    bool isSafeType(ParameterType type) const;
    bool verifyType(ParameterType type) const;

    virtual bool copy(const ParameterBase& other);
    virtual void copyUnsafe(const ParameterBase& other);
    virtual bool copyLerp(const ParameterBase& param1, const ParameterBase& param2, f32 t);

#ifdef SEAD_DEBUG
    virtual void genMessageParameter(sead::hostio::Context* context);
    void genMessageParameter(sead::hostio::Context* context, const sead::SafeString&);
    virtual void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                              const sead::hostio::PropertyEvent* event);
#endif

    virtual void writeToXML(sead::XmlElement* element, sead::Heap* heap);
    virtual bool readFromXML(const sead::XmlElement& element, bool x);

    virtual ParameterType getParameterType() const = 0;
    virtual const void* ptr() const = 0;
    virtual void* ptr() = 0;
    virtual const void* typePtr() const = 0;
    virtual void* typePtr() = 0;
    virtual u32 size() const = 0;
    virtual u32 calcBinarizeSize() const { return size(); }
    virtual ParameterBase* clone(sead::Heap* heap, IParameterObj* obj) const = 0;

    void applyResource(ResParameter res);
    void applyResource(ResParameter res, f32 t);
    void applyString(const sead::SafeString& string, bool x);
    virtual void postApplyResource_(const void*, size_t) {}
    void createByTypeName(const sead::SafeString& a, const sead::SafeString& b);

    virtual bool isBinary() const { return false; }
    virtual bool isBinaryInternalBuffer() const { return true; }
    bool isInterpolatable() const;
    size_t binarize(void* binary) const;
    bool makeZero();

    static u32 calcHash(const sead::SafeString& key);

    template <typename T>
    T* ptrT() {
        return static_cast<T*>(ptr());
    }

    template <typename T>
    const T* ptrT() const {
        return static_cast<const T*>(ptr());
    }

protected:
    friend class IParameterObj;

    template <typename T>
    void copyLerp_(const ParameterBase& param1, const ParameterBase& param2, f32 t);

    u32 mNameHash;
    ParameterBase* mNext;

#ifdef SEAD_DEBUG
    const char* mName;
    const char* mLabel;
    const char* mMeta;
#endif
};

using ParameterType = ParameterBase::ParameterType;

template <typename T>
class Parameter : public ParameterBase {
public:
    Parameter() = default;

    explicit Parameter(const T& value) : mValue(value) {}

    Parameter(const T& value, const sead::SafeString& name, IParameterObj* obj) {
        initializeParameter(value, name, name, obj);
    }

    Parameter(const T& value, const sead::SafeString& name, const sead::SafeString& label,
              IParameterObj* obj) {
        initializeParameter(value, name, label, obj);
    }

    Parameter(const T& value, const sead::SafeString& name, const sead::SafeString& label,
              const sead::SafeString& meta, IParameterObj* obj) {
        initializeParameter(value, name, label, meta, obj);
    }

    ~Parameter() override { ; }

    ParameterType getParameterType() const override {
        if constexpr (std::is_pointer<T>())
            return ParameterType::Special;
        else if constexpr (std::is_same<T, bool>())
            return ParameterType::Bool;
        else if constexpr (std::is_same<T, f32>())
            return ParameterType::F32;
        else if constexpr (std::is_same<T, s32>())
            return ParameterType::Int;
        else if constexpr (std::is_same<T, sead::Vector2f>())
            return ParameterType::Vec2;
        else if constexpr (std::is_same<T, sead::Vector3f>())
            return ParameterType::Vec3;
        else if constexpr (std::is_same<T, sead::Vector4f>())
            return ParameterType::Vec4;
        else if constexpr (std::is_same<T, sead::Color4f>())
            return ParameterType::Color;
        else if constexpr (std::is_same<T, sead::FixedSafeString<32>>())
            return ParameterType::String32;
        else if constexpr (std::is_same<T, sead::FixedSafeString<64>>())
            return ParameterType::String64;
        // TODO: curve1-4
        else if constexpr (std::is_same<T, sead::FixedSafeString<256>>())
            return ParameterType::String256;
        else if constexpr (std::is_same<T, sead::Quatf>())
            return ParameterType::Quat;
        else if constexpr (std::is_same<T, u32>())
            return ParameterType::U32;
        else if constexpr (std::is_same<T, sead::SafeString>())
            return ParameterType::StringRef;
        else
            static_assert(!std::is_same<T, T>(), "Unknown type");
    }

    const void* ptr() const override {
        if constexpr (std::is_base_of<sead::SafeString, T>()) {
            return mValue.cstr();
        } else {
            return &mValue;
        }
    }

    void* ptr() override {
        if constexpr (std::is_same<T, sead::SafeString>()) {
            SEAD_ASSERT_MSG(false, "Can't access.");
            return nullptr;
        } else if constexpr (std::is_base_of<sead::BufferedSafeString, T>()) {
            return mValue.getBuffer();
        } else {
            return &mValue;
        }
    }

    const void* typePtr() const override { return &mValue; }
    void* typePtr() override { return &mValue; }

    u32 size() const override {
        if constexpr (std::is_same<T, sead::SafeString>())
            return 8;
        else if constexpr (std::is_same<T, sead::FixedSafeString<32>>())
            return 32;
        else if constexpr (std::is_same<T, sead::FixedSafeString<64>>())
            return 64;
        else if constexpr (std::is_same<T, sead::FixedSafeString<256>>())
            return 256;
        else
            return sizeof(T);
    }

    u32 calcBinarizeSize() const override {
        if constexpr (std::is_base_of<sead::SafeString, T>()) {
            return mValue.calcLength() + 1;
        } else {
            return size();
        }
    }

    ParameterBase* clone(sead::Heap* heap, IParameterObj* obj) const override {
        return new (heap) Parameter<T>(mValue, getName(), getLabel(), getMeta(), obj);
    }

    void initializeParameter(const T& value, const sead::SafeString& name,
                             const sead::SafeString& label, IParameterObj* obj) {
        initializeListNode(name, label, "", obj);
        mValue = value;

        if constexpr (std::is_same<T, sead::SafeString>()) {
            SEAD_ASSERT_MSG(!sead::MemUtil::isStack(value.cstr()), "%p is in stack", value.cstr());
        }
    }

    void initializeParameter(const T& value, const sead::SafeString& name,
                             const sead::SafeString& label, const sead::SafeString& meta,
                             IParameterObj* obj) {
        initializeListNode(name, label, meta, obj);
        mValue = value;

        if constexpr (std::is_same<T, sead::SafeString>()) {
            SEAD_ASSERT_MSG(!sead::MemUtil::isStack(value.cstr()), "%p is in stack", value.cstr());
        }
    }

    /// Alias of initializeParameter.
    void init(const T& value, const sead::SafeString& name, IParameterObj* obj) {
        initializeParameter(value, name, name, obj);
    }

    /// Alias of initializeParameter.
    void init(const T& value, const sead::SafeString& name, const sead::SafeString& label,
              IParameterObj* obj) {
        initializeParameter(value, name, label, obj);
    }

    /// Alias of initializeParameter.
    void init(const T& value, const sead::SafeString& name, const sead::SafeString& label,
              const sead::SafeString& meta, IParameterObj* obj) {
        initializeParameter(value, name, label, meta, obj);
    }

    T& ref() { return mValue; }
    const T& ref() const { return mValue; }

    T& operator*() { return mValue; }
    const T& operator*() const { return mValue; }
    T* operator->() { return &mValue; }
    const T* operator->() const { return &mValue; }

    Parameter& operator=(const T& value) {
        mValue = value;
        return *this;
    }

protected:
    T mValue;
};

template <typename T>
class ParameterBuffer : public Parameter<T*> {
public:
    ParameterBuffer(sead::Heap* heap, s32 num) {
        SEAD_ASSERT(!isBinaryInternalBuffer());
        this->mValue = new (heap) T[num];
        mBufferSize = num;
        mBufferAllocated = true;

        for (s32 i = 0; i < num; ++i)
            this->mValue[i] = {};
    }

    ~ParameterBuffer() override { freeBuffer(); }

    void freeBuffer() {
        if (!mBufferAllocated)
            return;

        if (this->mValue)
            delete[] this->mValue;
        mBufferAllocated = false;
    }

    ParameterType getParameterType() const override {
        if constexpr (std::is_same<T, s32>())
            return ParameterType::BufferInt;
        else if constexpr (std::is_same<T, f32>())
            return ParameterType::BufferF32;
        else if constexpr (std::is_same<T, u32>())
            return ParameterType::BufferU32;
        else if constexpr (std::is_same<T, u8>())
            return ParameterType::BufferBinary;
        else
            static_assert(!std::is_same<T, T>(), "Unknown type");
    }

    const void* ptr() const override { return this->mValue; }
    void* ptr() override { return this->mValue; }
    u32 size() const override { return sizeof(T) * mBufferSize; }

    void postApplyResource_(const void* data, size_t size) override {
        if (isBinaryInternalBuffer())
            return;
        this->mValue = data;
        mBufferSize = size / sizeof(T);
    }

    bool isBinary() const override { return true; }
    bool isBinaryInternalBuffer() const override { return mBufferAllocated; }

protected:
    s32 mBufferSize;
    bool mBufferAllocated;
};

class ParameterDirection3f : public Parameter<sead::Vector3f> {
public:
    ~ParameterDirection3f() override = default;

#ifdef SEAD_DEBUG
    void genMessageParameter(sead::hostio::Context* context) override;
    void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                      const sead::hostio::PropertyEvent* event) override;
#endif
};

template <u32 N>
class ParameterCurve : public ParameterBase {
public:
    ParameterCurve(const sead::SafeString& name, const sead::SafeString& label,
                   IParameterObj* param_obj);

    void reset();

    bool copy(const ParameterBase& other) override;
    void copyUnsafe(const ParameterBase& other) override;

    void writeToXML(sead::XmlElement* element, sead::Heap* heap) override;
    bool readFromXML(const sead::XmlElement& element, bool x) override;

    ParameterType getParameterType() const override;

    const void* ptr() const override { return mCurveData.data(); }
    void* ptr() override { return mCurveData.data(); }
    const void* typePtr() const override { return mCurveData.data(); }
    void* typePtr() override { return mCurveData.data(); }
    u32 size() const override { return sizeof(mCurveData); }

    ParameterBase* clone(sead::Heap* heap, IParameterObj* obj) const override;

    void postApplyResource_(const void*, size_t size) override;

#ifdef SEAD_DEBUG
    void genMessageParameter(sead::hostio::Context* context) override;
    virtual void genMessageParameterUnit(sead::hostio::Context* context, s32,
                                         const sead::SafeString&, const sead::SafeString&);
#endif

    static constexpr u32 cUnitCurveParamNum = 30;

protected:
    std::array<sead::hostio::Curve<f32>, N> mCurves;
    std::array<sead::hostio::CurveData, N> mCurveData;
};

inline ResParameter getResParameter(const agl::utl::ResParameterObj& obj,
                                    const sead::SafeString& name) {
    const s32 idx = obj.searchIndex(ParameterBase::calcHash(name));
    if (idx == -1)
        return {};

    return obj.getResParameter(idx);
}

inline ResParameterObj getResParameterObj(const agl::utl::ResParameterList& list,
                                          const sead::SafeString& name) {
    const s32 idx = list.searchObjIndex(ParameterBase::calcHash(name));
    if (idx == -1)
        return {};

    return list.getResParameterObj(idx);
}

inline ResParameterList getResParameterList(const agl::utl::ResParameterList& list,
                                            const sead::SafeString& name) {
    const s32 idx = list.searchListIndex(ParameterBase::calcHash(name));
    if (idx == -1)
        return {};

    return list.getResParameterList(idx);
}

}  // namespace agl::utl

#define AGL_UTILS_PARAMETER_H_
#include "agl/Utils/aglParameterCurve.hpp"
#undef AGL_UTILS_PARAMETER_H_
