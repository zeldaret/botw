#include <ore/BitUtils.h>

namespace ore {

void BitArray::SetAllOn() {
    const int num = m_num_bits >> ShiftAmount;
    Fill(num, Word(-1));

    u32 remainder = u32(m_num_bits) % NumBitsPerWord;
    if (remainder != 0)
        m_words[num] = (1ul << remainder) - 1;
}

void BitArray::SetAllOff() {
    Fill(GetNumWords(), Word(0));
}

BitArray::TestIter BitArray::BeginTest() const {
    return TestIter(m_words, m_words + GetNumWords());
}

BitArray::TestIter BitArray::EndTest() const {
    return TestIter(nullptr, nullptr);
}

BitArray::TestClearIter BitArray::BeginTestClear() {
    return TestClearIter(m_words, m_words + GetNumWords());
}

BitArray::TestClearIter BitArray::EndTestClear() {
    return TestClearIter(nullptr, nullptr);
}

BitArray::TestIter::TestIter(const BitArray::Word* start, const BitArray::Word* end) {
    for (auto* it = start; it != end; ++it) {
        if (*it != 0) {
            auto idx = CountTrailingZeros(*it);
            idx += 8 * int(intptr_t(it) - intptr_t(start)) & ClearMask;
            m_bit = idx;
            m_current_word = it;
            m_last_word = end;
            m_next = *it & (*it - 1);
            return;
        }
    }

    SetInvalid();
}

BitArray::TestIter& BitArray::TestIter::operator++() {
    m_bit &= ClearMask;

    // Fast path: we still have bits in the current word
    if (m_next != 0) {
        m_bit += CountTrailingZeros(m_next);
        m_next &= m_next - 1;
        return *this;
    }

    // Find the next nonzero word and the first set bit in it
    ++m_current_word;
    for (; m_current_word != m_last_word; ++m_current_word) {
        m_bit += NumBitsPerWord;
        if (*m_current_word == 0)
            continue;
        m_bit += CountTrailingZeros(*m_current_word);
        m_next = *m_current_word & (*m_current_word - 1);
        return *this;
    }

    SetInvalid();
    return *this;
}

BitArray::TestClearIter::TestClearIter(BitArray::Word* start, BitArray::Word* end) {
    for (auto* it = start; it != end; ++it) {
        if (*it != 0) {
            auto idx = CountTrailingZeros(*it);
            idx += 8 * int(intptr_t(it) - intptr_t(start)) & ClearMask;
            m_bit = idx;
            m_current_word = it;
            m_last_word = end;
            m_next = *it & (*it - 1);
            return;
        }
    }

    SetInvalid();
}

BitArray::TestClearIter& BitArray::TestClearIter::operator++() {
    m_bit &= ClearMask;

    if (m_next != 0) {
        m_bit += CountTrailingZeros(m_next);
        m_next &= m_next - 1;
        return *this;
    }

    *m_current_word = 0;
    ++m_current_word;
    for (; m_current_word != m_last_word; *m_current_word = 0, ++m_current_word) {
        m_bit += NumBitsPerWord;
        if (*m_current_word == 0)
            continue;
        m_bit += CountTrailingZeros(*m_current_word);
        m_next = *m_current_word & (*m_current_word - 1);
        return *this;
    }

    SetInvalid();
    return *this;
}

}  // namespace ore
