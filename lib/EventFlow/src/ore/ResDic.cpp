#include <algorithm>
#include <ore/ResDic.h>
#include <ore/ResEndian.h>

namespace ore {

int ResDic::FindRefBit(const StringView& str1, const StringView& str2) {
    const auto len1 = str1.size();
    const auto len2 = str2.size();
    const auto len = std::max(len1, len2);

    for (int bit_idx = 0; bit_idx < 8 * len; ++bit_idx) {
        const int idx = bit_idx >> 3;

        int bit1 = 0;
        if (len1 > idx)
            bit1 = str1[len1 + -(idx + 1)] >> (bit_idx % 8) & 1;

        int bit2 = 0;
        if (len2 > idx)
            bit2 = str2[len2 + -(idx + 1)] >> (bit_idx % 8) & 1;

        if (bit1 != bit2)
            return bit_idx;
    }

    return -1;
}

void SwapEndian(ResEndian* endian, ResDic* dic) {
    const auto swap_entries = [&] {
        const int num_entries = dic->num_entries + 1;
        for (int i = 0; i < num_entries; ++i) {
            ResDicEntry& entry = dic->GetEntries()[i];
            SwapEndian(&entry.compact_bit_idx);
            SwapEndian(&entry.next_indices[0]);
            SwapEndian(&entry.next_indices[1]);
        }
    };

    if (endian->is_serializing) {
        swap_entries();
        SwapEndian(&dic->num_entries);
    } else {
        SwapEndian(&dic->num_entries);
        swap_entries();
    }
}

}  // namespace ore
