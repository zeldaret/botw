#pragma once

constexpr int HK_SHAPE_BUFFER_SIZE = 512;

struct hkpShapeBufferStorage {
    alignas(16) char m_storage[HK_SHAPE_BUFFER_SIZE];

    template <typename T>
    operator T*() {  // NOLINT(google-explicit-constructor)
        return reinterpret_cast<T*>(m_storage);
    }
};

using hkpShapeBuffer = hkpShapeBufferStorage;
