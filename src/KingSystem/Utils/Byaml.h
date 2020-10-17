#pragma once

/// BYML / BYAML utilities which seem to have been imported from Super Mario Odyssey.

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/Utils/Types.h"

namespace al {

struct ByamlData;

enum class ByamlType {
    Invalid = 0,

    String = 0xa0,
    Binary = 0xa1,

    Array = 0xc0,
    Hash = 0xc1,
    StringTable = 0xc2,

    Bool = 0xd0,
    Int = 0xd1,
    Float = 0xd2,
    UInt = 0xd3,
    Int64 = 0xd4,
    UInt64 = 0xd5,
    Double = 0xd6,

    Null = 0xff,
};

class ByamlIter {
public:
    ByamlIter();
    explicit ByamlIter(const u8* data);
    ByamlIter(const u8* data, const u8* root_node);
    ByamlIter(const ByamlIter& other);

    ByamlIter& operator=(const ByamlIter& rhs);

    bool isValid() const;
    bool isTypeHash() const;
    bool isTypeArray() const;
    bool isTypeContainer() const;

    bool isExistKey(const char* key) const;
    s32 getKeyIndex(const char* key) const;

    s32 getSize() const;

    void getByamlDataByIndex(ByamlData* data, s32 index) const;
    bool getByamlDataByKey(ByamlData* data, const char* key) const;
    bool getByamlDataByKeyIndex(ByamlData* data, s32 index) const;
    ByamlIter getIterByIndex(s32 index) const;
    ByamlIter getIterByKey(const char* key) const;
    bool getKeyName(const char** key, s32 index) const;

    bool tryGetIterByIndex(ByamlIter* iter, s32 index) const;
    bool tryGetIterByKey(ByamlIter* iter, const char* key) const;
    bool tryGetIterAndKeyNameByIndex(ByamlIter* iter, const char** key, s32 index) const;

    bool tryGetStringByIndex(const char** value, s32 index) const;
    bool tryGetStringByKey(const char** value, const char* key) const;
    bool tryConvertString(const char** value, const ByamlData* data) const;

    bool tryGetIntByIndex(s32* value, s32 index) const;
    bool tryGetIntByKey(s32* value, const char* key) const;

    bool tryGetUIntByIndex(u32* value, s32 index) const;
    bool tryGetUIntByKey(u32* value, const char* key) const;
    bool tryConvertUInt(u32* value, const ByamlData* data) const;

    bool tryGetFloatByIndex(f32* value, s32 index) const;
    bool tryGetFloatByKey(f32* value, const char* key) const;

    bool tryGetBoolByIndex(bool* value, s32 index) const;
    bool tryGetBoolByKey(bool* value, const char* key) const;

    bool isEqualData(const ByamlIter& other) const;

private:
    const u8* mData = nullptr;
    const u8* mRootNode = nullptr;
};

class ByamlStringTableIter {
public:
    explicit ByamlStringTableIter(const u8* data) : mData(data) {}

    const char* getString(s32 index) const;
    s32 findStringIndex(const char* string) const;

private:
    const u8* mData;
};

class ByamlArrayIter {
public:
    explicit ByamlArrayIter(const u8* data);

    const u8* getDataTable() const;
    bool getDataByIndex(ByamlData* data, s32 index);

private:
    const u8* mData;
};

class ByamlHashIter {
public:
    explicit ByamlHashIter(const u8* data);

    s32 getSize() const;
    const u8* getPairTable() const;
    bool getDataByIndex(ByamlData* data, s32 index) const;
    bool getDataByKey(ByamlData* data, s32 key_index) const;
    const u8* findPair(s32 key_index) const;
    const u8* getPairByIndex(s32 index) const;

private:
    const u8* mData;
};

struct ByamlHeader {
    u16 getTag() const;
    bool isInvertHeader() const;
    u16 getVersion() const;
    u16 getHashKeyTableOffset() const;
    u16 getStringTableOffset() const;
    u16 getDataOffset() const;

    u16 magic;
    u16 version;
    u32 hash_key_table_offset;
    u32 string_table_offset;
    u32 data_offset;
};
KSYS_CHECK_SIZE_NX150(ByamlHeader, 0x10);

struct ByamlContainerHeader {
    ByamlType getType() const;
    u32 getCount(bool byteswap) const;

    u32 type_and_size;
};

struct ByamlHashPair {
    u32 getKey(bool byteswap) const;
    ByamlType getType() const;
    u32 getValue(bool byteswap) const;

    u32 name_and_type;
    u32 value;
};

struct ByamlData {
    u32 getValue() const { return value; }
    ByamlType getType() const { return type; }

    void set(const ByamlHashPair* pair, bool byteswap);
    void set(u8, u32, bool byteswap);

    u32 value = 0;
    sead::SizedEnum<ByamlType, u8> type = ByamlType::Invalid;
};

bool tryGetByamlS32(s32* value, const ByamlIter& iter, const char* key);
bool tryGetByamlU32(u32* value, const ByamlIter& iter, const char* key);
bool tryGetByamlF32(f32* value, const ByamlIter& iter, const char* key);
bool tryGetByamlV3f(sead::Vector3f* value, const ByamlIter& iter, const char* key);

}  // namespace al
