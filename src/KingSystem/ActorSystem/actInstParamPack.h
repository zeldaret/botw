#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadMemUtil.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProc;

class InstParamPack {
public:
    enum class EntryType {
        /// Signed(?) 32-bit integer.
        Int = 0,
        /// Unknown.
        _1 = 1,
        /// Single-precision float.
        Float = 2,
        /// Boolean.
        Bool = 3,
        /// Vector3f.
        Vec3 = 4,
        /// String (stored inline).
        String = 5,
        /// Unsigned 64-bit integer. Can be used to store pointers.
        UInt64 = 6,
        /// 3x4 matrix (sead::Matrix34).
        Matrix34 = 7,
    };

    using ActorCallback = sead::IDelegate1<BaseProc*>;

    struct Entry {
        union Data {
            s32 i;
            f32 f;
            u32 type1;
            u64 l;
            bool b;
            sead::Vector3f vec3;
            sead::Matrix34f mtx34;
            const char* str;
            ActorCallback* cb;
        };
        KSYS_CHECK_SIZE_NX150(Data, 0x30);

        const char* key;
        sead::SizedEnum<EntryType, s8> type;
        Data data;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x40);

    class Buffer {
    public:
        Buffer() { clear(); }
        Buffer& operator=(const Buffer& other);

        void clear();
        void add(const void* data, const sead::SafeString& name, s32 byte_size, EntryType type);
        void add(ActorCallback* callback, const sead::SafeString& name);

        void add(int data, const sead::SafeString& name) {
            add(&data, name, sizeof(data), EntryType::Int);
        }

        void add(u32 data, const sead::SafeString& name) { add(static_cast<int>(data), name); }

        void add(float data, const sead::SafeString& name) {
            add(&data, name, sizeof(data), EntryType::Float);
        }

        void add(bool data, const sead::SafeString& name) {
            add(&data, name, sizeof(data), EntryType::Bool);
        }

        void add(const sead::Matrix34f& data, const sead::SafeString& name) {
            add(&data, name, sizeof(data), EntryType::Matrix34);
        }

        bool pop(s32* position, Entry* out_entry);

    private:
        void writeBytes(const void* value, s32 size) {
            sead::MemUtil::copy(&mData[mPosition], value, size);
            mPosition += size;
        }

        template <typename T>
        void write(const T& value) {
            writeBytes(&value, sizeof(value));
        }

        template <typename T>
        bool read(T& value, s32* position) {
            if (*position + s32(sizeof(T)) > mData.size())
                return false;

            sead::MemUtil::copy(&value, &mData[*position], sizeof(T));
            *position += s32(sizeof(T));
            return true;
        }

        u16 mNumItems;
        s16 mPosition;
        sead::SafeArray<u8, 0xc0> mData;
    };
    KSYS_CHECK_SIZE_NX150(Buffer, 0xc4);

    InstParamPack() = default;
    virtual ~InstParamPack() = default;

    Buffer& getBuffer() { return mBuffer; }
    const Buffer& getBuffer() const { return mBuffer; }

    Buffer* operator->() { return &mBuffer; }
    const Buffer* operator->() const { return &mBuffer; }

private:
    BaseProc* mProc = nullptr;
    Buffer mBuffer;
};
KSYS_CHECK_SIZE_NX150(InstParamPack, 0xd8);

}  // namespace ksys::act
