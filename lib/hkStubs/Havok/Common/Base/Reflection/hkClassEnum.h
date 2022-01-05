#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkCustomAttributes;
class hkStreamWriter;

class hkClassEnum {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkClassEnum)
    HK_DECLARE_REFLECTION()

    class Item {
    public:
        HK_DECLARE_CLASS_ALLOCATOR(Item)
        HK_DECLARE_REFLECTION()

        constexpr Item(int v, const char* n) : m_value(v), m_name(n) {}

        const char* getName() const { return m_name; }
        int getValue() const { return m_value; }

    private:
        int m_value;
        const char* m_name;
    };

    enum FlagValues { FLAGS_NONE = 0 };
    using Flags = hkFlags<FlagValues, hkUint32>;

    hkClassEnum(const char* name, const Item* items, int numItems);

    constexpr hkClassEnum(const char* name, const Item* items, int numItems,
                          hkCustomAttributes* attributes, hkUint32 flags)
        : m_name(name), m_items(items), m_numItems(numItems), m_attributes(attributes),
          m_flags(flags) {}

    const char* getName() const;
    int getNumItems() const;
    const hkClassEnum::Item& getItem(int i) const;
    hkResult getNameOfValue(int val, const char** name) const;
    hkResult getValueOfName(const char* name, int* val) const;
    hkResult decomposeFlags(int flagValue, hkArray<const char*>& bitsOut, int& bitsOver) const;
    hkUint32 getSignature() const;
    void writeSignature(hkStreamWriter* w) const;
    const hkVariant* getAttribute(const char* name) const;
    inline const Flags& getFlags() const;
    inline Flags& getFlags();

private:
    const char* m_name;
    const class Item* m_items;
    int m_numItems;
    hkCustomAttributes* m_attributes;
    Flags m_flags;
};

inline hkClassEnum::hkClassEnum(const char* name, const hkClassEnum::Item* items, int numItems)
    : m_name(name), m_items(items), m_numItems(numItems), m_attributes(nullptr), m_flags(0) {}

inline const char* hkClassEnum::getName() const {
    return m_name;
}

inline int hkClassEnum::getNumItems() const {
    return m_numItems;
}

inline const hkClassEnum::Item& hkClassEnum::getItem(int i) const {
    return m_items[i];
}

inline const hkClassEnum::Flags& hkClassEnum::getFlags() const {
    return m_flags;
}

inline hkClassEnum::Flags& hkClassEnum::getFlags() {
    return m_flags;
}
