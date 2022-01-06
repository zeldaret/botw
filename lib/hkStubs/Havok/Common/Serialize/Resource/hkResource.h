#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkTypeInfoRegistry;

class hkResource : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkResource)

    struct Export {
        HK_DECLARE_CLASS_ALLOCATOR(Export)

        const char* name;
        void* data;
    };

    struct Import {
        HK_DECLARE_CLASS_ALLOCATOR(Import)

        const char* name;
        void** location;
    };

    virtual const char* getName() const = 0;

    ~hkResource() override = default;

    virtual void callDestructors() {}

    virtual void getImportsExports(hkArray<Import>& impOut, hkArray<Export>& expOut) const = 0;

    virtual void* getContentsPointer(const char* typeName,
                                     const hkTypeInfoRegistry* typeRegistry) const = 0;

    template <typename T>
    inline T* getContentsWithRegistry(const hkTypeInfoRegistry* typeRegistry) const;

    template <typename T>
    inline T* getContents() const;

    /// Return the top level object type name.
    virtual const char* getContentsTypeName() const = 0;
};
