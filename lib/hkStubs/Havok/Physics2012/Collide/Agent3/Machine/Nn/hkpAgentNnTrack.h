#pragma once

#include <Havok/Common/Base/hkBase.h>

#define HK_AGENT3_MIDPHASE_AGENT_SIZE 80
#define HK_AGENT3_NARROWPHASE_AGENT_SIZE 160
#define HK_AGENT3_MAX_AGENT_SIZE 160
#define HK_AGENT3_SECTOR_SIZE 960

struct hkpAgentNnEntry;

enum hkpAgentNnTrackType {
    HK_AGENT3_INVALID_TRACK = 0,
    HK_AGENT3_MIDPHASE_TRACK = 1,
    HK_AGENT3_NARROWPHASE_TRACK = 2,
};

struct hkpAgentNnSector {
    HK_DECLARE_CLASS_ALLOCATOR(hkpAgentNnSector)

    hkpAgentNnEntry* getBegin() { return reinterpret_cast<hkpAgentNnEntry*>(m_data); }

    hkpAgentNnEntry* getEnd() {
        return reinterpret_cast<hkpAgentNnEntry*>(m_data + HK_AGENT3_SECTOR_SIZE);
    }

    hkUint8 m_data[HK_AGENT3_SECTOR_SIZE];
};

struct hkpAgentNnTrack {
    HK_DECLARE_CLASS_ALLOCATOR(hkpAgentNnTrack)

    explicit hkpAgentNnTrack(hkpAgentNnTrackType nnTrackType) {
        m_bytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;
        m_nnTrackType = nnTrackType;
    }

    int getSectorSize(int sectorIndex) const;
    HK_FORCE_INLINE static unsigned int getAgentSize(hkpAgentNnTrackType nnTrackType);
    HK_FORCE_INLINE unsigned int getAgentSize() const;

    hkUint16 m_bytesUsedInLastSector;

    /// Does the track contain midphase or narrowphase agent entries?
    hkEnum<hkpAgentNnTrackType, hkUint8> m_nnTrackType;
    hkUint8 m_padding;

    hkInplaceArray<hkpAgentNnSector*, 1> m_sectors;
};

inline int hkpAgentNnTrack::getSectorSize(int sectorIndex) const {
    if (sectorIndex + 1 == m_sectors.getSize()) {
        return m_bytesUsedInLastSector;
    }
    return HK_AGENT3_SECTOR_SIZE;
}

inline unsigned int hkpAgentNnTrack::getAgentSize(hkpAgentNnTrackType nnTrackType) {
    return nnTrackType * HK_AGENT3_MIDPHASE_AGENT_SIZE;
}

inline unsigned int hkpAgentNnTrack::getAgentSize() const {
    return getAgentSize(m_nnTrackType);
}
