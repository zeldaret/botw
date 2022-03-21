#pragma once

#include <ore/Types.h>

namespace ore {

struct RelocationTable {
    struct Section {
        struct Entry {
            /// Offset to pointers to relocate
            int pointers_offset;
            /// Bit field that determines which pointers need to be relocated
            /// (next to 32 contiguous pointers starting from the listed offset)
            u32 mask;
        };

        void SetPtr(void* ptr_);
        void* GetPtr() const;
        void* GetPtrInFile(void* base) const;
        void* GetBasePtr(void* base) const;
        u32 GetSize() const;

        u64 ptr;
        int offset;
        int size;
        int first_entry_idx;
        int num_entries;
    };

    u32 magic;
    int table_start_offset;
    int num_sections;
    Section sections[1];

    Section* GetSections() { return sections; }
    const Section* GetSections() const { return sections; }

    Section::Entry* GetEntries() {
        return reinterpret_cast<Section::Entry*>(GetSections() + num_sections);
    }
    const Section::Entry* GetEntries() const {
        return reinterpret_cast<const Section::Entry*>(GetSections() + num_sections);
    }

    void Relocate();
    void Unrelocate();
    static int CalcSize(int num_sections, int num_entries);
};

}  // namespace ore
