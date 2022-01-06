#pragma once

#include <Havok/Common/Base/Reflection/hkClass.h>
#include <Havok/Common/Base/hkBase.h>

class hkRootLevelContainer {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkRootLevelContainer)
    HK_DECLARE_REFLECTION()

public:
    HK_FORCE_INLINE hkRootLevelContainer();
    HK_FORCE_INLINE hkRootLevelContainer(const hkRootLevelContainer& other);
    explicit hkRootLevelContainer(hkFinishLoadedObjectFlag f);

    HK_FORCE_INLINE ~hkRootLevelContainer();

    hkRootLevelContainer& operator=(const hkRootLevelContainer&) = default;

    class NamedVariant {
    public:
        HK_DECLARE_CLASS_ALLOCATOR(hkRootLevelContainer::NamedVariant)
        HK_DECLARE_REFLECTION()

        HK_FORCE_INLINE NamedVariant();
        explicit NamedVariant(hkFinishLoadedObjectFlag flag);

        NamedVariant(const char* name, void* object, const hkClass* klass);
        NamedVariant(const char* name, const hkVariant& v);

        HK_FORCE_INLINE void set(const char* name, void* object, const hkClass* klass);
        HK_FORCE_INLINE void set(const char* name, const hkVariant& v);

        HK_FORCE_INLINE const char* getTypeName() const;
        HK_FORCE_INLINE const char* getName() const;
        HK_FORCE_INLINE void* getObject() const;
        HK_FORCE_INLINE const hkClass* getClass() const;
        HK_FORCE_INLINE const hkRefVariant& getRefVariant() const;

    private:
        hkStringPtr m_name;
        hkStringPtr m_className;
        hkRefVariant m_variant;
    };

    template <typename T>
    inline T* findObject(const void* prevObject = nullptr) const;

    void* findObjectByType(const char* typeName, const void* prevObject = nullptr) const;
    void* findObjectByName(const char* objectName, const void* prevObject = nullptr) const;

    hkArray<NamedVariant> m_namedVariants;
};

inline hkRootLevelContainer::hkRootLevelContainer() = default;

inline hkRootLevelContainer::hkRootLevelContainer(const hkRootLevelContainer& other) {
    *this = other;
}

inline hkRootLevelContainer::~hkRootLevelContainer() = default;

template <typename T>
inline T* hkRootLevelContainer::findObject(const void* prevObject) const {
    if (void* p = findObjectByType(T::staticClass().getName(), prevObject))
        return static_cast<T*>(p);
    return nullptr;
}

inline hkRootLevelContainer::NamedVariant::NamedVariant() = default;

inline void hkRootLevelContainer::NamedVariant::set(const char* name, void* object,
                                                    const hkClass* klass) {
    m_name = name;
    m_variant.set(object, klass);
    m_className = m_variant.getClass() ? m_variant.getClass()->getName() : nullptr;
}

inline void hkRootLevelContainer::NamedVariant::set(const char* name, const hkVariant& v) {
    m_name = name;
    m_variant = v;
    m_className = m_variant.getClass() ? m_variant.getClass()->getName() : nullptr;
}

inline const char* hkRootLevelContainer::NamedVariant::getTypeName() const {
    return m_variant.getClass() ? m_variant.getClass()->getName() :
                                  static_cast<const char*>(m_className);
}

inline const char* hkRootLevelContainer::NamedVariant::getName() const {
    return m_name;
}

inline void* hkRootLevelContainer::NamedVariant::getObject() const {
    return m_variant.val();
}

inline const hkClass* hkRootLevelContainer::NamedVariant::getClass() const {
    return m_variant.getClass();
}

inline const hkRefVariant& hkRootLevelContainer::NamedVariant::getRefVariant() const {
    return m_variant;
}
