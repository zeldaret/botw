#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkStridedVertices {
    HK_DECLARE_CLASS_ALLOCATOR(hkStridedVertices)

    hkStridedVertices() : m_numVertices(0) {}
    explicit hkStridedVertices(const hkArrayBase<hkVector4>& vertices) { set(vertices); }
    hkStridedVertices(const hkVector4* vertices, int count) { set(vertices, count); }

    int getSize() const { return m_numVertices; }

    void getVertex(int index, hkVector4& vertexOut) const {
        const auto* v = reinterpret_cast<const hkReal*>(
            reinterpret_cast<const hkUint8*>(m_vertices) + m_striding * index);
        vertexOut.set(v[0], v[1], v[2], m_striding >= int(sizeof(hkVector4)) ? v[3] : 0);
    }

    void set(const hkArrayBase<hkVector4>& vertices) { set(vertices.begin(), vertices.getSize()); }

    template <typename T>
    void set(const T* vertices, int numVertices) {
        m_vertices = reinterpret_cast<const hkReal*>(vertices);
        m_numVertices = numVertices;
        m_striding = sizeof(T);
    }

    const hkReal* m_vertices;
    int m_numVertices;
    int m_striding;
};
