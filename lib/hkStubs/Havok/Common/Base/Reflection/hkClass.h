#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkClassEnum;
class hkClassMember;
class hkCustomAttributes;
class hkStreamWriter;
class hkTypedUnion;

template <typename Key, typename Value>
class hkPointerMap;

class hkClass {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkClass)
    HK_DECLARE_REFLECTION()

    enum SignatureFlags {
        SIGNATURE_LOCAL = 1,
    };

    enum FlagValues {
        FLAGS_NONE = 0,
        FLAGS_NOT_SERIALIZABLE = 1,
    };
    using Flags = hkFlags<FlagValues, hkUint32>;

    // Note: this is not constexpr and this is the reason Havok code is littered with
    // static constructor functions that call this hkClass constructor at runtime
    // even though everything could have been initialised at compile time.
    hkClass(const char* className, const hkClass* parentClass, int objectSizeInBytes,
            const hkClass** implementedInterfaces, int numImplementedInterfaces,
            const hkClassEnum* declaredEnums, int numDeclaredEnums,
            const hkClassMember* declaredMembers, int numDeclaredMembers,
            const void* defaults = nullptr, const hkCustomAttributes* attributes = nullptr,
            hkUint32 flags = 0, hkUint32 version = 0);

    const char* getName() const;
    bool equals(const hkClass* other) const;

    const hkClass* getParent() const;
    hkClass* getParent();
    int getInheritanceDepth() const;
    hkBool isSuperClass(const hkClass& k) const;
    const hkClass* getInterface(int i) const;
    int getNumInterfaces() const;
    const hkClass* getDeclaredInterface(int i) const;
    int getNumDeclaredInterfaces() const;

    const hkClassEnum& getEnum(int i) const;
    const hkClassEnum* getEnumByName(const char* name) const;
    int getNumEnums() const;
    const hkClassEnum& getDeclaredEnum(int i) const;
    const hkClassEnum* getDeclaredEnumByName(const char* name) const;
    int getNumDeclaredEnums() const;

    const hkClassMember& getMember(int i) const;
    hkClassMember& getMember(int i);
    const hkClassMember* getMemberByName(const char* name) const;
    int getMemberIndexByName(const char* name) const;
    int getMemberIndexByNameCaseInsensitive(const char* name) const;
    int getNumMembers() const;
    const hkClassMember& getDeclaredMember(int i) const;
    const hkClassMember* getDeclaredMemberByName(const char* name) const;
    int getDeclaredMemberIndexByName(const char* name) const;
    int getNumDeclaredMembers() const;

    int getObjectSize() const;
    void setObjectSize(int size);

    hkBool hasVtable() const;

    hkBool32 hasDefault(int memberIndex) const;
    hkBool32 hasDeclaredDefault(int declaredIndex) const;
    hkResult getDefault(int memberIndex, hkStreamWriter* w) const;
    const void* getDefault(int memberIndex) const;
    hkResult getDeclaredDefault(int declaredIndex, hkStreamWriter* w) const;
    hkResult getDefault(int memberIndex, hkTypedUnion& value) const;
    const void* getDeclaredDefault(int memberIndex) const;
    hkResult getDeclaredDefault(int declaredIndex, hkTypedUnion& value) const;

    hkUint32 getSignature(int signatureFlags = 0) const;
    int getDescribedVersion() const;
    void writeSignature(hkStreamWriter* w) const;

    const hkVariant* getAttribute(const char* id) const;

    const Flags& getFlags() const;
    Flags& getFlags();

    using UpdateFlagFromClassMap = hkPointerMap<const hkClass*, hkInt32>;
    static void updateMetadataInplace(hkClass** c, int sourceVersion);
    static void updateMetadataInplace(hkClass* c, UpdateFlagFromClassMap& updatedAlready,
                                      int sourceVersion);

private:
    hkResult retrieveMember(int memberIndex, const void*& defaultOut,
                            const hkClassMember*& memberOut) const;

protected:
    const char* m_name;
    const hkClass* m_parent;
    int m_objectSize;
    int m_numImplementedInterfaces;
    const class hkClassEnum* m_declaredEnums;
    int m_numDeclaredEnums;
    const class hkClassMember* m_declaredMembers;
    int m_numDeclaredMembers;
    const void* m_defaults;
    const hkCustomAttributes* m_attributes;
    Flags m_flags;
    int m_describedVersion;
};
