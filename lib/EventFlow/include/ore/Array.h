#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <ore/Allocator.h>
#include <ore/Buffer.h>
#include <ore/IterRange.h>
#include <type_traits>

namespace ore {

// This is like a std::span, not a fixed-size array like std::array.
// Elements will NOT be automatically freed.
template <typename T>
class Array {
public:
    Array() = default;
    Array(T* data, int size) : m_data(data), m_size(size) {}

    T* data() const { return m_data; }
    int size() const { return m_size; }

    auto begin() const { return data(); }
    auto end() const { return data() + size(); }

    T& operator[](int idx) { return m_data[idx]; }
    const T& operator[](int idx) const { return m_data[idx]; }

    T& front() { return m_data[0]; }
    const T& front() const { return m_data[0]; }

    T& back() { return m_data[m_size - 1]; }
    const T& back() const { return m_data[m_size - 1]; }

    void SetBuffer(void* new_buffer, int num) {
        DestructElements();
        m_data = static_cast<T*>(new_buffer);
        m_size = num;
    }

    void SetBuffer(int num, Allocator* allocator) {
        auto* new_buffer = allocator->AllocImpl(num * int(sizeof(T)), alignof(std::max_align_t));
        SetBuffer(new_buffer, num);
    }

    void ConstructElements(int num, Allocator* allocator) {
        SetBuffer(num, allocator);
        DefaultConstructElements();
    }

    void ConstructElements(void* new_buffer, int num) {
        SetBuffer(new_buffer, num);
        DefaultConstructElements();
    }

    void ConstructElements(Buffer buffer) {
        DestructElements();
        m_data = reinterpret_cast<T*>(buffer.data);
        m_size = buffer.size / int(sizeof(T));
        DefaultConstructElements();
    }

    void DestructElements() { std::destroy(begin(), end()); }

    void ClearWithoutFreeing() {
        DestructElements();
        m_data = nullptr;
        m_size = 0;
    }

    void Clear(Allocator* allocator) {
        if (!m_data)
            return;
        auto* data = m_data;
        ClearWithoutFreeing();
        allocator->Free(data);
    }

    void DefaultConstructElements() {
        for (auto it = begin(), e = end(); it != e;)
            new (it++) T;
    }

    void UninitializedDefaultConstructElements() {
        std::uninitialized_default_construct(begin(), end());
    }

private:
    T* m_data{};
    int m_size{};
};

template <typename T>
class SelfDestructingArray : public Array<T> {
public:
    ~SelfDestructingArray() { this->DestructElements(); }
};

template <typename T>
class ArrayListBase {
public:
    ArrayListBase() : m_data(), m_size(), m_capacity() {}
    ArrayListBase(T* data, int capacity) {
        m_size = 0;
        m_data = data;
        m_capacity = capacity;
    }
    ~ArrayListBase() { clear(); }

    ArrayListBase(const ArrayListBase&) = delete;
    auto operator=(const ArrayListBase&) = delete;

    T* begin() { return m_data; }
    const T* begin() const { return m_data; }

    T* end() { return m_data + m_size; }
    const T* end() const { return m_data + m_size; }

    T* data() { return m_data; }
    const T* data() const { return m_data; }

    int size() const { return m_size; }
    int capacity() const { return m_capacity; }

    T& operator[](int idx) { return m_data[idx]; }
    const T& operator[](int idx) const { return m_data[idx]; }

    T& front() { return m_data[0]; }
    const T& front() const { return m_data[0]; }

    T& back() { return m_data[m_size - 1]; }
    const T& back() const { return m_data[m_size - 1]; }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        auto* item = new (&m_data[m_size++]) T(std::forward<Args>(args)...);
        return *item;
    }

    void push_back(const T& item) { new (&m_data[m_size++]) T(item); }

    void pop_back() {
        std::destroy_at(&back());
        --m_size;
    }

    void clear() {
        std::destroy(begin(), end());
        m_size = 0;
    }

    T* m_data;
    int m_size;
    int m_capacity;
};

template <typename T, int N>
class FixedArrayList : public ArrayListBase<T> {
public:
    FixedArrayList() : ArrayListBase<T>(reinterpret_cast<T*>(m_storage), N) {}

private:
    std::aligned_storage_t<sizeof(T), alignof(T)> m_storage[N];
};

// This is like a std::vector.
template <typename T>
class DynArrayList : public ArrayListBase<T> {
public:
    DynArrayList() = default;
    explicit DynArrayList(Allocator* allocator) : m_allocator(allocator) {}

    ~DynArrayList() {
        clear();
        m_allocator = nullptr;
        this->m_size = 0;
    }

    void Reset() {
        clear();
        m_allocator = nullptr;
    }

    DynArrayList(const DynArrayList&) = delete;
    auto operator=(const DynArrayList&) = delete;

    void Init(Allocator* allocator, int initial_capacity = 1) {
        clear();
        m_allocator = allocator;
        Reallocate(initial_capacity);
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        GrowIfNeeded();
        return ArrayListBase<T>::emplace_back(std::forward<Args>(args)...);
    }

    void push_back(const T& item) {
        GrowIfNeeded();
        return ArrayListBase<T>::push_back(item);
    }

    void clear() {
        std::destroy(this->begin(), this->end());
        auto* data = this->m_data;
        this->m_data = nullptr;
        this->m_size = 0;
        this->m_capacity = 0;
        Free(data);
    }

    template <typename InputIterator>
    void OverwriteWith(InputIterator src_begin, InputIterator src_end) {
        const int src_size = std::distance(src_begin, src_end);
        if (src_size > this->m_capacity) {
            this->m_size = 0;
            Reallocate(2 * src_size);
        }
        this->m_size = src_size;
        std::uninitialized_copy(src_begin, src_end, this->begin());
    }

    /// Quadratic complexity; only use this for small copies.
    template <typename Range>
    void DeduplicateCopy(const Range& range) {
        for (auto it = range.begin(), end = range.end(); it != end; ++it) {
            auto value = *it;
            if (std::find_if(range.begin(), it, [&](const auto& v) { return value == v; }) == it)
                this->emplace_back(value);
        }
    }

    /// Resize the array so that it contains `new_size` elements.
    ///
    /// - If the new size is greater than the current size, new elements are added and
    ///   default initialized. Iterators may be invalidated.
    /// - If the new size is less than the current size, excess elements are destroyed.
    ///
    /// @param new_size The new size of the array.
    void Resize(int new_size) {
        if (this->m_capacity < new_size)
            Reallocate(new_size);

        if (this->m_size < new_size) {
            std::uninitialized_default_construct(this->m_data + this->m_size,
                                                 this->m_data + new_size);
        } else {
            std::destroy(this->m_data + new_size, this->m_data + this->m_size);
        }

        this->m_size = new_size;
    }

private:
    void GrowIfNeeded() {
        if (this->m_size < this->m_capacity)
            return;
        Reallocate(2 * this->m_size + 2);
    }

    void Reallocate(int new_capacity) {
        const int num_bytes = sizeof(T) * new_capacity;
        auto* new_buffer =
            static_cast<T*>(m_allocator->AllocImpl(num_bytes, alignof(std::max_align_t)));
        auto* old_buffer = this->m_data;
        auto* capacity = &this->m_capacity;
        UninitializedCopyTo(new_buffer);
        this->m_data = new_buffer;
        *capacity = new_capacity;
        Free(old_buffer);
    }

    void UninitializedCopyTo(T* destination) const {
        std::uninitialized_copy(this->begin(), this->end(), destination);
    }

    void Free(void* ptr) {
        if (ptr)
            m_allocator->Free(ptr);
    }

    Allocator* m_allocator{};
};

}  // namespace ore
