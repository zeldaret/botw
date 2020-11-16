#include "KingSystem/Utils/Byaml/Byaml.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadMemUtil.h>
#include "KingSystem/Utils/Byaml/ByamlArrayIter.h"
#include "KingSystem/Utils/Byaml/ByamlData.h"
#include "KingSystem/Utils/Byaml/ByamlHashIter.h"
#include "KingSystem/Utils/Byaml/ByamlLocal.h"
#include "KingSystem/Utils/Byaml/ByamlStringTableIter.h"

namespace al {

ByamlIter::ByamlIter() : mData(nullptr), mRootNode(nullptr) {}

ByamlIter::ByamlIter(const u8* data) {
    mData = data;
    mRootNode = nullptr;
    if (mData) {
        if (ByamlLocalUtil::verifiByaml(mData)) {
            const ByamlHeader* header = reinterpret_cast<const ByamlHeader*>(mData);
            u32 data_root_offset = header->getDataOffset();
            if (data_root_offset) {
                mRootNode = &mData[data_root_offset];
            }
        } else {
            mData = nullptr;
            mRootNode = nullptr;
        }
    }
}

ByamlIter::ByamlIter(const u8* data, const u8* root_node) : mData(data), mRootNode(root_node) {}

ByamlIter::ByamlIter(const ByamlIter& other) : mData(other.mData), mRootNode(other.mRootNode) {}

ByamlIter& ByamlIter::operator=(const ByamlIter& rhs) {
    if (this != &rhs) {
        // This is formally undefined behavior because ByamlIter is not trivially copyable
        // (since it has non-trivial copy constructors and copy assignment operators)
        // but those are effectively trivial so this will work in practice.
        // This is what Nintendo did and it is required for matching.
        sead::MemUtil::copy(this, &rhs, sizeof(*this));
    }
    return *this;
}

bool ByamlIter::isValid() const {
    return mData != nullptr;
}

bool ByamlIter::isTypeHash() const {
    const ByamlContainerHeader* node = reinterpret_cast<const ByamlContainerHeader*>(mRootNode);
    return node && node->getType() == ByamlType::Hash;
}

bool ByamlIter::isTypeArray() const {
    const ByamlContainerHeader* node = reinterpret_cast<const ByamlContainerHeader*>(mRootNode);
    return node && node->getType() == ByamlType::Array;
}

bool ByamlIter::isTypeContainer() const {
    return isTypeArray() || isTypeHash();
}

bool ByamlIter::isExistKey(const char* key) const {
    if (!mRootNode) {
        return false;
    }

    if (!isTypeHash()) {
        return false;
    }

    const s32 index = getKeyIndex(key);
    if (index < 0) {
        return 0;
    }

    ByamlHashIter node_hash(mRootNode);
    return node_hash.findPair(index);
}

s32 ByamlIter::getKeyIndex(const char* key) const {
    const ByamlStringTableIter table = ByamlLocalUtil::getHashKeyTableIter(mData);
    return table.findStringIndex(key);
}

s32 ByamlIter::getSize() const {
    if (!mRootNode) {
        return 0;
    }

    if (isTypeContainer()) {
        return ByamlLocalUtil::getContainerSize(mRootNode);
    }

    return 0;
}

ByamlIter ByamlIter::getIterByIndex(s32 index) const {
    ByamlData data;
    if (!getByamlDataByIndex(&data, index)) {
        return ByamlIter();
    }

    return getIterFromData(data);
}

ByamlIter ByamlIter::getIterByKey(const char* key) const {
    ByamlData data;
    if (!getByamlDataByKey(&data, key)) {
        return ByamlIter();
    }

    return getIterFromData(data);
}

ByamlIter ByamlIter::getIterFromData(const ByamlData& data) const {
    if (data.getType() == ByamlType::Hash || data.getType() == ByamlType::Array) {
        return ByamlIter(mData, &mData[data.getValue()]);
    }

    if (data.getType() == ByamlType::Null) {
        return ByamlIter(mData, nullptr);
    }

    return ByamlIter();
}

bool ByamlIter::getByamlDataByIndex(ByamlData* data, s32 index) const {
    if (isTypeArray()) {
        ByamlArrayIter array_node(mRootNode);
        return array_node.getDataByIndex(data, index);
    } else if (isTypeHash()) {
        ByamlHashIter hash_node(mRootNode);
        return hash_node.getDataByIndex(data, index);
    }

    return false;
}

bool ByamlIter::getByamlDataByKey(ByamlData* data, const char* key) const {
    if (!isTypeHash()) {
        return false;
    }

    auto* header = reinterpret_cast<const al::ByamlHeader*>(mData);
    const s32 offset = header->getHashKeyTableOffset();
    if (!offset) {
        return false;
    }
    const ByamlStringTableIter table = ByamlStringTableIter(&mData[offset]);

    ByamlHashIter hash_node(mRootNode);
    const s32 size = hash_node.getSize();
    if (size < 1) {
        return false;
    }

    // Binary Search
    const ByamlHashPair* pair;
    s32 start = 0;
    s32 end = size;
    s32 index;
    while (true) {
        if (start >= end) {
            return false;
        }

        index = (start + end) / 2;
        pair = hash_node.getPairByIndex(index);
        const char* str = table.getString(pair->getKey());
        s32 result = std::strcmp(key, str);
        if (result == 0)
            break;
        if (result > 0)
            start = index + 1;
        else if (result < 0)
            end = index;
    }

    data->set(pair);

    return true;
}

bool ByamlIter::getByamlDataAndKeyNameByIndex(ByamlData* data, const char** key, s32 index) const {
    if (!isTypeHash()) {
        return false;
    }

    const ByamlHashIter hash_iter(mRootNode);
    const ByamlHashPair* pair = hash_iter.getPairByIndex(index);
    if (!pair) {
        return false;
    }

    if (data) {
        data->set(pair);
    }

    ByamlStringTableIter table_iter = ByamlLocalUtil::getHashKeyTableIter(mData);
    *key = table_iter.getString(pair->getKey());
    return true;
}

bool ByamlIter::getKeyName(const char** key, s32 index) const {
    if (!mRootNode) {
        return false;
    }

    if (!isTypeHash()) {
        return false;
    }

    ByamlHashIter hash_node(mRootNode);
    const ByamlHashPair* pair = hash_node.getPairByIndex(index);
    if (!pair) {
        return false;
    }

    const ByamlStringTableIter hash_table = ByamlLocalUtil::getHashKeyTableIter(mData);
    *key = hash_table.getString(pair->getKey());

    return true;
}

bool ByamlIter::tryGetIterByIndex(ByamlIter* iter, s32 index) const {
    *iter = getIterByIndex(index);
    return iter->isValid();
}

bool ByamlIter::tryGetIterByKey(ByamlIter* iter, const char* key) const {
    *iter = getIterByKey(key);
    return iter->isValid();
}

bool ByamlIter::tryGetIterAndKeyNameByIndex(ByamlIter* iter, const char** key, s32 index) const {
    ByamlData data;
    if (!getByamlDataAndKeyNameByIndex(&data, key, index)) {
        *key = nullptr;
        return tryGetIterByIndex(iter, index);
    }

    *iter = getIterFromData(data);
    return true;
}

bool ByamlIter::tryGetStringByIndex(const char** value, s32 index) const {
    ByamlData data;
    if (!getByamlDataByIndex(&data, index)) {
        return false;
    }

    return tryConvertString(value, &data);
}

bool ByamlIter::tryGetStringByKey(const char** value, const char* key) const {
    ByamlData data;
    if (!getByamlDataByKey(&data, key)) {
        return false;
    }

    return tryConvertString(value, &data);
}

bool ByamlIter::tryConvertString(const char** value, const ByamlData* data) const {
    if (data->getType() != ByamlType::String) {
        return false;
    }

    const auto string_table = ByamlLocalUtil::getStringTableIter(mData);
    *value = string_table.getString(data->getValue());

    return true;
}

bool ByamlIter::tryGetIntByIndex(s32* value, s32 index) const {
    ByamlData data;
    if (!getByamlDataByIndex(&data, index)) {
        return false;
    }

    return tryConvertInt(value, &data);
}

bool ByamlIter::tryGetIntByKey(s32* value, const char* key) const {
    ByamlData data;
    if (!getByamlDataByKey(&data, key)) {
        return false;
    }

    return tryConvertInt(value, &data);
}

bool ByamlIter::tryConvertInt(s32* value, const ByamlData* data) const {
    if (data->getType() != ByamlType::Int) {
        return false;
    }

    *value = data->getValue();
    return true;
}

bool ByamlIter::tryGetUIntByIndex(u32* value, s32 index) const {
    ByamlData data;
    if (!getByamlDataByIndex(&data, index)) {
        return false;
    }

    return tryConvertUInt(value, &data);
}

bool ByamlIter::tryGetUIntByKey(u32* value, const char* key) const {
    ByamlData data;
    if (!getByamlDataByKey(&data, key)) {
        return false;
    }

    return tryConvertUInt(value, &data);
}

bool ByamlIter::tryConvertUInt(u32* value, const ByamlData* data) const {
    if (data->getType() == ByamlType::Int) {
        s32 signed_value = data->getValue<s32>();
        if (signed_value < 0) {
            *value = 0;
            return false;
        } else {
            *value = signed_value;
            return true;
        }
    } else if (data->getType() == ByamlType::UInt) {
        *value = data->getValue();
        return true;
    }

    return false;
}

bool ByamlIter::tryGetFloatByIndex(f32* value, s32 index) const {
    ByamlData data;
    if (!getByamlDataByIndex(&data, index)) {
        return false;
    }

    return tryConvertFloat(value, &data);
}

bool ByamlIter::tryGetFloatByKey(f32* value, const char* key) const {
    ByamlData data;
    if (!getByamlDataByKey(&data, key)) {
        return false;
    }

    return tryConvertFloat(value, &data);
}

bool ByamlIter::tryConvertFloat(f32* value, const ByamlData* data) const {
    if (data->getType() != ByamlType::Float) {
        return false;
    }

    *value = data->getValue<f32>();
    return true;
}

bool ByamlIter::tryGetBoolByIndex(bool* value, s32 index) const {
    ByamlData data;
    if (!getByamlDataByIndex(&data, index)) {
        return false;
    }

    return tryConvertBool(value, &data);
}

bool ByamlIter::tryGetBoolByKey(bool* value, const char* key) const {
    ByamlData data;
    if (!getByamlDataByKey(&data, key)) {
        return false;
    }

    return tryConvertBool(value, &data);
}

bool ByamlIter::tryConvertBool(bool* value, const ByamlData* data) const {
    if (data->getType() != ByamlType::Bool) {
        return false;
    }

    *value = data->getValue() != 0;
    return true;
}

bool ByamlIter::isEqualData(const ByamlIter& other) const {
    if (!mData || !other.mData) {
        return false;
    }

    return mData == other.mData && mRootNode == other.mRootNode;
}

}  // namespace al
