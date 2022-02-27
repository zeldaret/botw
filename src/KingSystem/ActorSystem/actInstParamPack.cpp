#include "KingSystem/ActorSystem/actInstParamPack.h"
#include <prim/seadMemUtil.h>

namespace ksys::act {

void InstParamPack::Buffer::clear() {
    mNumItems = 0;
    mPosition = 0;
    mData.fill(0);
}

// NON_MATCHING: write()
void InstParamPack::Buffer::add(const void* data, const sead::SafeString& name, s32 byte_size,
                                InstParamPack::EntryType type) {
    if (byte_size + mPosition + u32(sizeof(const char*)) + 1 > mData.getByteSize()) {
        SEAD_ASSERT_MSG(false, "InstParamPack::Buffer::add: Buffer overflow");
        return;
    }

    write(name.cstr());
    write(u8(type));
    writeBytes(data, byte_size);
    ++mNumItems;
}

// NON_MATCHING: write()
void InstParamPack::Buffer::add(ActorCallback* callback, const sead::SafeString& name) {
    add(callback, name, sizeof(callback), EntryType::UInt64);
}

// NON_MATCHING
bool InstParamPack::Buffer::pop(s32* position, InstParamPack::Entry* out_entry) {
    if (!read(out_entry->key, position))
        return false;

    if (!read(out_entry->type.mValue, position))
        return false;

    switch (out_entry->type) {
    case EntryType::Int:
        return read(out_entry->data.i, position);
    case EntryType::UInt:
        return read(out_entry->data.type1, position);
    case EntryType::Float:
        return read(out_entry->data.f, position);
    case EntryType::Bool:
        return read(out_entry->data.b, position);
    case EntryType::Vec3:
        return read(out_entry->data.vec3, position);
    case EntryType::String: {
        const s32 start_pos = *position;
        char c;
        do {
            if (!read(c, position)) {
                out_entry->data.str = nullptr;
                return false;
            }
        } while (c != sead::SafeString::cNullChar);
        out_entry->data.str = reinterpret_cast<const char*>(&mData[start_pos]);
        return true;
    }
    case EntryType::UInt64:
        return read(out_entry->data.l, position);
    case EntryType::Matrix34:
        return read(out_entry->data.mtx34, position);
    default:
        return false;
    }
}

InstParamPack::Buffer& InstParamPack::Buffer::operator=(const InstParamPack::Buffer& other) {
    size_t pos = other.mPosition;
    mPosition = pos;
    mNumItems = other.mNumItems;
    sead::MemUtil::copy(mData.getBufferPtr(), other.mData.getBufferPtr(), pos);
    return *this;
}

}  // namespace ksys::act
