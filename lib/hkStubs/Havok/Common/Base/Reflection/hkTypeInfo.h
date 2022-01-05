#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <cstring>
#include <type_traits>

class hkClass;

class hkTypeInfo {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkTypeInfo)

    using FinishLoadedObjectFunction = void (*)(void*, int);
    using CleanupLoadedObjectFunction = void (*)(void*);

    template <typename T>
    HK_ALWAYS_INLINE static hkTypeInfo make(const char* name, const char* scopedName) {
        FinishLoadedObjectFunction finish = nullptr;
        constexpr bool needsFinish = std::is_constructible_v<T, hkFinishLoadedObjectFlag>;
        if constexpr (needsFinish)
            finish = finishFunctionImpl<T>;

        CleanupLoadedObjectFunction cleanup = cleanupFunctionImpl<T>;

        const void* vtable = nullptr;
        if constexpr (std::is_polymorphic_v<T>) {
            static_assert(needsFinish, "polymorphic types must have a finish constructor");
            vtable = getVtableFunctionImpl<T>();
        }

        return hkTypeInfo{name, scopedName, finish, cleanup, vtable, sizeof(T)};
    }

    hkTypeInfo(const char* name, const char* scopedName, FinishLoadedObjectFunction finish,
               CleanupLoadedObjectFunction cleanup, const void* vtable, hk_size_t size)
        : m_typeName(name), m_scopedName(scopedName), m_finishLoadedObjectFunction(finish),
          m_cleanupLoadedObjectFunction(cleanup), m_vtable(vtable), m_size(size) {}

    const char* getTypeName() const { return m_typeName; }
    const char* getScopedName() const { return m_scopedName; }
    const void* getVtable() const { return m_vtable; }
    void cleanupLoadedObject(void* ptr) const;
    void finishLoadedObject(void* ptr, int finishFlag) const;
    void finishLoadedObjectWithoutTracker(void* ptr, int finishFlag) const;

    hkBool hasFinishFunction() const { return m_finishLoadedObjectFunction != nullptr; }
    hkBool hasCleanupFunction() const { return m_cleanupLoadedObjectFunction != nullptr; }
    hk_size_t getSize() const { return m_size; }
    hkBool isVirtual() const { return m_vtable != nullptr; }

private:
    template <typename T>
    HK_VISIBILITY_HIDDEN static void finishFunctionImpl(void* p, int finishing) {
        hkFinishLoadedObjectFlag flag{finishing};
        new (p) T{flag};
    }

    template <typename T>
    HK_VISIBILITY_HIDDEN static void cleanupFunctionImpl(void* p) {
        static_cast<T*>(p)->~T();
    }

    template <typename T>
    HK_VISIBILITY_HIDDEN static const void* getVtableFunctionImpl() {
        // The following trick only works because all Havok polymorphic types are supposed
        // to have hkBaseObject as the most-base class -- forcing the vtable to be at offset 0.
        //
        // Unfortunately we can't check if hkBaseObject is at offset 0, but let's at least
        // verify that hkBaseObject is a base class of T.
        static_assert(std::is_base_of_v<hkBaseObject, T>,
                      "polymorphic types must have hkBaseObject as a base");

        union {
            alignas(16) void* dummy;
            std::aligned_storage_t<sizeof(T), alignof(T)> obj;
        };
        hkFinishLoadedObjectFlag flag;
        new (static_cast<void*>(std::addressof(obj))) T{flag};

        const void* vtable_ptr;
        std::memcpy(&vtable_ptr, &obj, sizeof(vtable_ptr));
        return vtable_ptr;
    }

    const char* m_typeName;
    const char* m_scopedName;
    FinishLoadedObjectFunction m_finishLoadedObjectFunction;
    CleanupLoadedObjectFunction m_cleanupLoadedObjectFunction;
    const void* m_vtable;
    hk_size_t m_size;
};
