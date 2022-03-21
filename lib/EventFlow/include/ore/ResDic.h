#pragma once

#include <ore/BinaryFile.h>
#include <ore/StringView.h>
#include <ore/Types.h>

namespace ore {

struct ResEndian;

struct ResDicEntry {
    StringView GetKey() const { return *name.Get(); }

    // Bits 3-7: index of the byte that should be checked
    // Bits 0-2: index of the bit in that byte
    int compact_bit_idx;
    u16 next_indices[2];
    BinTPtr<BinString> name;
};

struct ResDic {
    static int FindRefBit(const StringView& str1, const StringView& str2);

    const ResDicEntry* FindEntry(const StringView& key) const {
        auto* prev = &entries[0];
        auto* entry = &entries[prev->next_indices[0]];
        while (prev->compact_bit_idx < entry->compact_bit_idx) {
            const int bit_idx = entry->compact_bit_idx;
            long bit = 0;
            if (u32(key.length()) > u32(bit_idx >> 3))
                bit = ((key[key.length() + -((bit_idx >> 3) + 1)] >> (bit_idx & 7))) & 1;

            prev = entry;
            entry = &entries[prev->next_indices[bit]];
        }
        return entry;
    }

    /// Returns the index for the specified key or -1 if it cannot be found.
    int FindIndex(const StringView& key) const {
        const auto* entry = FindEntry(key);
        const auto entry_name = entry->GetKey();
        bool ok = [&] { return StringView(key.data(), key.length()) == entry_name; }();
        if (!ok)
            return -1;
        return static_cast<int>(entry - &GetEntries()[1]);
    }

    /// Entry 0 is the root entry.
    ResDicEntry* GetEntries() { return entries; }
    /// Entry 0 is the root entry.
    const ResDicEntry* GetEntries() const { return entries; }

    u32 magic;
    int num_entries;
    ResDicEntry entries[1];
    // Followed by ResDicEntry[num_entries].
};

void SwapEndian(ResEndian* endian, ResDic* dic);

}  // namespace ore
