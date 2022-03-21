#include <cstring>
#include <ore/RelocationTable.h>

namespace ore {

namespace {

struct BitFlag32 {
    explicit BitFlag32(u32 flags) : m_flags(flags) {}
    bool operator[](int idx) const { return m_flags & (1 << idx); }

    u32 m_flags{};
};

}  // namespace

void RelocationTable::Section::SetPtr(void* ptr_) {
    ptr = reinterpret_cast<u64>(ptr_);
}

void* RelocationTable::Section::GetPtr() const {
    return reinterpret_cast<void*>(ptr);
}

void* RelocationTable::Section::GetPtrInFile(void* base) const {
    return static_cast<char*>(base) + offset;
}

void* RelocationTable::Section::GetBasePtr(void* base) const {
    if (ptr)
        base = reinterpret_cast<void*>(ptr - offset);
    return base;
}

u32 RelocationTable::Section::GetSize() const {
    return size;
}

void RelocationTable::Relocate() {
    char* const table_base = reinterpret_cast<char*>(this) - table_start_offset;
    const auto* entries = GetEntries();
    const int num = num_sections;

    for (int section_idx = 0; section_idx < num; ++section_idx) {
        const auto& section = GetSections()[section_idx];

        auto* base = static_cast<char*>(section.GetBasePtr(table_base));
        const int idx0 = section.first_entry_idx;
        const int end = idx0 + section.num_entries;

        for (int idx = idx0; idx < end; ++idx) {
            const auto& entry = entries[idx];
            const auto pointers_offset = entry.pointers_offset;
            const BitFlag32 mask{entry.mask};

            auto* pointer_ptr = reinterpret_cast<u64*>(table_base + pointers_offset);
            for (int i = 0; i < 32; ++i, ++pointer_ptr) {
                if (!mask[i])
                    continue;
                const auto offset = static_cast<int>(*pointer_ptr);
                void* ptr = offset == 0 ? nullptr : reinterpret_cast<void*>(base + offset);
                std::memcpy(pointer_ptr, &ptr, sizeof(ptr));
            }
        }
    }
}

void RelocationTable::Unrelocate() {
    char* const table_base = reinterpret_cast<char*>(this) - table_start_offset;
    const auto* entries = GetEntries();
    const int num = num_sections;

    for (int section_idx = 0; section_idx < num; ++section_idx) {
        auto& section = GetSections()[section_idx];

        auto* base = static_cast<char*>(section.GetBasePtr(table_base));
        section.SetPtr(nullptr);
        const int idx0 = section.first_entry_idx;
        const int end = idx0 + section.num_entries;

        for (int idx = idx0; idx < end; ++idx) {
            const auto& entry = entries[idx];
            const auto pointers_offset = entry.pointers_offset;
            const BitFlag32 mask{entry.mask};

            auto* pointer_ptr = reinterpret_cast<void**>(table_base + pointers_offset);
            for (int i = 0; i < 32; ++i, ++pointer_ptr) {
                if (!mask[i])
                    continue;
                void* ptr = *pointer_ptr;
                u64 offset = static_cast<int>(ptr == nullptr ? 0 : intptr_t(ptr) - intptr_t(base));
                std::memcpy(pointer_ptr, &offset, sizeof(offset));
            }
        }
    }
}

int RelocationTable::CalcSize(int num_sections, int num_entries) {
    int size = 0;
    size += offsetof(RelocationTable, sections);
    size += sizeof(Section) * num_sections;
    size += sizeof(Section::Entry) * num_entries;
    return size;
}

}  // namespace ore
