#ifndef SEAD_RUNTIMETYPEINFO_H_
#define SEAD_RUNTIMETYPEINFO_H_

namespace sead
{
namespace RuntimeTypeInfo
{
class Interface
{
public:
    Interface() {}

    virtual bool isDerived(const Interface* typeInfo) const = 0;
};

class Root : public Interface
{
public:
    Root() {}

    bool isDerived(const Interface* typeInfo) const override { return typeInfo == this; }
};

template <typename BaseType>
class Derive : public Interface
{
public:
    Derive() {}

    bool isDerived(const Interface* typeInfo) const override
    {
        if (this == typeInfo)
            return true;

        const RuntimeTypeInfo::Interface* rootTypeInfo = BaseType::getRuntimeTypeInfoStatic();
        return rootTypeInfo->isDerived(typeInfo);
    }
};

}  // namespace RuntimeTypeInfo

/// Tests if the object is a DerivedType or any type that derives from (i.e. inherits) DerivedType.
template <typename DerivedType, typename Type>
inline bool IsDerivedFrom(const Type* obj)
{
    const RuntimeTypeInfo::Interface* typeInfo = DerivedType::getRuntimeTypeInfoStatic();
    return obj != nullptr && obj->checkDerivedRuntimeTypeInfo(typeInfo);
}

/// If the object is a DerivedType or any type that derives from (i.e. inherits) DerivedType,
/// this returns obj casted to DerivedType* -- otherwise this returns nullptr.
///
/// @note This is similar to C++'s dynamic_cast or LLVM's dyn_cast but only works with types
/// that use the sead RTTI mechanism.
template <typename DerivedType, typename Type>
inline DerivedType* DynamicCast(Type* obj)
{
    if (IsDerivedFrom<DerivedType, Type>(obj))
        return static_cast<DerivedType*>(obj);

    return nullptr;
}

}  // namespace sead

/// Use this macro to declare sead RTTI machinery for a base class.
/// You must use SEAD_RTTI_OVERRIDE in all derived classes.
/// @param CLASS The name of the class.
#define SEAD_RTTI_BASE(CLASS)                                                                      \
public:                                                                                            \
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic()                      \
    {                                                                                              \
        static const sead::RuntimeTypeInfo::Root typeInfo;                                         \
        return &typeInfo;                                                                          \
    }                                                                                              \
                                                                                                   \
    static bool checkDerivedRuntimeTypeInfoStatic(                                                 \
        const sead::RuntimeTypeInfo::Interface* typeInfo)                                          \
    {                                                                                              \
        const sead::RuntimeTypeInfo::Interface* clsTypeInfo = CLASS::getRuntimeTypeInfoStatic();   \
        return typeInfo == clsTypeInfo;                                                            \
    }                                                                                              \
                                                                                                   \
    virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo)     \
        const                                                                                      \
    {                                                                                              \
        return checkDerivedRuntimeTypeInfoStatic(typeInfo);                                        \
    }                                                                                              \
                                                                                                   \
    virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const                     \
    {                                                                                              \
        return getRuntimeTypeInfoStatic();                                                         \
    }

/// Use this macro to declare sead RTTI machinery for a derived class.
/// @param CLASS The name of the class.
/// @param BASE The name of the base class of CLASS.
#define SEAD_RTTI_OVERRIDE(CLASS, BASE)                                                            \
public:                                                                                            \
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic()                      \
    {                                                                                              \
        static const sead::RuntimeTypeInfo::Derive<BASE> typeInfo;                                 \
        return &typeInfo;                                                                          \
    }                                                                                              \
                                                                                                   \
    static bool checkDerivedRuntimeTypeInfoStatic(                                                 \
        const sead::RuntimeTypeInfo::Interface* typeInfo)                                          \
                                                                                                   \
    {                                                                                              \
        const sead::RuntimeTypeInfo::Interface* clsTypeInfo = CLASS::getRuntimeTypeInfoStatic();   \
        if (typeInfo == clsTypeInfo)                                                               \
            return true;                                                                           \
                                                                                                   \
        return BASE::checkDerivedRuntimeTypeInfoStatic(typeInfo);                                  \
    }                                                                                              \
                                                                                                   \
    bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo)             \
        const override                                                                             \
    {                                                                                              \
        return checkDerivedRuntimeTypeInfoStatic(typeInfo);                                        \
    }                                                                                              \
                                                                                                   \
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override                    \
    {                                                                                              \
        return getRuntimeTypeInfoStatic();                                                         \
    }

#endif  // SEAD_RUNTIMETYPEINFO_H_
