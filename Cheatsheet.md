# Breath of the Wild Decompilation Cheatsheet

## Things to try when a function has major differences

The following actions should help when basic blocks are in the wrong order, or when there are weird issues that involve comparisons or conditionals:

* Invert conditionals.
* Introduce inline functions. Or manually inline code.
* Add or eliminate return statements.
* Duplicate or deduplicate code.
* Independent memory loads/stores can be reordered, so you might need to reorder statements or conditions in the source code. For example, `if (x || y)` might have to be written as `if (y || x)`.
* Turn if/else into ternaries and vice versa. This doesn't always make a difference, though.
* uintptr_t do not always produce the same code as pointers, even for simple operations such as comparisons.
* Loops:
    * Index-based loops
        * u32 / s32 can make a difference, in particular for loop unrolling.
        * `<` vs `!=` can affect codegen. If the trip count is known at compile-time, Clang will usually change `<` into `!=`, but you should still try `<` first.
        * In some rare cases, Nintendo will use `!=` instead of `<`.
    * Iterator loops
        * Since we are targeting C++17, the preferred way to iterate over a container is to use a range-based for loop (e.g. `for (auto x : array)`).
        * Sometimes, making the iterator appear explicitly is required to match the original code. Example: `for (auto it = array.begin(), end = array.end(); it != end; ++it)`
        * In some rare cases, the end iterator is not kept in a variable, and instead it's recalculated at the end of each iteration. Example: `for (auto it = array.begin(); it != array.end(); ++it)`
        * Sometimes it is possible to use `<algorithm>` functions (e.g. std::for_each, std::all_of, etc.) for simpler loops.
        * And in some very rare cases (when dealing with EventFlow for example) it is sometimes *required* to use `<algorithm>` to match.

## Minor differences

* Incorrect comparison flags (getting >= instead of > for example)
    * Invert conditionals.
    * For integers: make sure you are using the correct signedness.
        * For example, HI means that you should be using an unsigned integer.
    * For floating-point, keep in mind that `x > 5.0` and `!(x <= 5.0)` are not equivalent because of NaN. This can reveal how an if/else statement is supposed to be written.

* Swapped CSEL operands
    * Invert conditionals. (For ternaries, also swap the ? and : operands, obviously.)
    * In some rare cases, `ptr == nullptr` and `!ptr` do not generate the same code.

* Extraneous function prologue/epilogue: this can happen when returning references. Change the return type to a pointer.

## sinit / static initializer / cxa_atexit

* If the second argument of a `_cxa_atexit` call is nullptr and the destructor is a nullsub, the object in question is likely a C-style array (not a std::array or a sead::SafeArray).

## Inline functions

This section lists some inline functions that are often used throughout the codebase.

### sead

sead is Nintendo's C++ standard library. It provides basic data structures such as strings and tree maps and many other essential components (e.g. threads, critical sections, file IO, etc.)


#### Strings

##### `sead::SafeString` constructor

```cpp
x.vptr = &sead::SafeString::vt;
x.cstr = "some string here";
```
⬇️
```cpp
sead::SafeString x = "some string here";
```

Note that the SafeString constructor is also implicitly called whenever a string literal is converted into an sead::SafeString (because it was passed as an argument to a function that expects an sead::SafeString for example).

---

##### `sead::FixedSafeString<N>` constructor

A `sead::FixedSafeString<N>` is a fixed-length SafeString. It derives from sead::BufferedSafeString (which derives from sead::SafeString) and contains a char[N] buffer right after the length.

Note: the field assignments may be in a different order.

```cpp
x._.cstr = (char*)&xxx; // some buffer right after `x`
x._.vptr = &`vtable for'sead::BufferedSafeStringBase<char>;
x.length = N; // where N is a number
sead::BufferedSafeStringBase<char>::assureTerminationImpl_(&x);
*x._.cstr = sead::SafeStringBase<char>::cNullChar;
x._.vptr = ...;
```
⬇️
```cpp
sead::FixedSafeString<N> x;
```

---

##### sead::SafeString::cstr

sead::SafeString::cstr returns a `const char*`, like std::string::c_str. You can expect it to be called whenever a SafeString needs to be passed to a function that takes a C-style string (`const char*`).

```cpp
string.vptr->assureTermination(...);
const char* ptr = string.cstr;
// do stuff with string.cstr
// note that the variable may not exist in the pseudocode
```
⬇️
```cpp
const char* ptr = string.cstr();
```


---

##### sead::SafeString::calcLength

```cpp
x.vptr->assureTermination(&x);
v12 = x.cstr;
str_length = 0LL;
v14 = (signed __int64)(v12 + 1);
while ( v12[str_length] != sead::SafeStringBase<char>::cNullChar )
{
  if ( *(unsigned __int8 *)(v14 + str_length) == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
  {
    LODWORD(str_length) = str_length + 1;
    break;
  }
  if ( *(unsigned __int8 *)(v14 + str_length + 1) == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
  {
    LODWORD(str_length) = str_length + 2;
    break;
  }
  v15 = str_length + 2;
  str_length += 3LL;
  if ( v15 >= 0x80000 )
  {
    LODWORD(str_length) = 0;
    break;
  }
}
```
⬇️
```cpp
s32 str_length = x.calcLength();
```

Note that this function is commonly called from other sead::SafeString inline functions.

---

##### sead::BufferedSafeString::copy

```cpp
dest_cstr = dest_safestring.cstr;
source_safestring.vptr->assureTermination(&source_safestring);
source_cstr = source_safestring.cstr;
if ( dest_cstr != source_cstr )
{
  source_safestring.vptr->assureTermination(&source_safestring);
  v6 = 0LL;
  v7 = (signed __int64)(source_safestring.cstr + 1);
  while ( source_safestring.cstr[v6] != sead::SafeStringBase<char>::cNullChar )
  {
    if ( *(unsigned __int8 *)(v7 + v6) == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
    {
      LODWORD(v6) = v6 + 1;
      break;
    }
    if ( *(unsigned __int8 *)(v7 + v6 + 1) == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
    {
      LODWORD(v6) = v6 + 2;
      break;
    }
    v8 = v6 + 2;
    v6 += 3LL;
    if ( v8 >= 0x80000 )
    {
      LODWORD(v6) = 0;
      break;
    }
  }
  if ( (signed int)v6 >= dest_safestring.length )
    LODWORD(v6) = dest_safestring.length - 1;
  v9 = (signed int)v6;
  memcpy_0(dest_str, source_str, (signed int)v6);
  dest_str[v9] = sead::SafeStringBase<char>::cNullChar;
}
```
⬇️
```cpp
dest_safestring = source_safestring;
```

Note: the while loop comes from an inlined version of sead::SafeString::calcLength.

---

##### sead::SafeString::startsWith

```cpp
if ( sead::SafeStringBase<char>::cNullChar != 'E' )
{
  v11 = string->cstr;
  v12 = "nemy";
  v13 = 'E';
  while ( (unsigned __int8)*v11 == v13 )
  {
    v14 = (unsigned __int8)*v12++;
    v13 = v14;
    ++v11;
    if ( v14 == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
      goto LABEL;
  }
  foo();
}
LABEL:
  bar();
```
⬇️
```cpp
if (string.startsWith("Enemy"))
    bar();
else
    foo();
```

This weird optimization can lead to malformed strings in Hex-Rays's output for strings that contain Japanese or multibyte characters more generally.

---

##### sead::SafeString::isEqual / operator==

```cpp
enemy->vptr->assureTermination(enemy);
enemy->vptr->assureTermination(enemy);
v15 = enemy->cstr;
if ( v15 == "Enemy_Assassin_Junior" )
{
LABEL_37:
  foo();
}
else
{
  v16 = 0LL;
  do
  {
    v17 = (unsigned __int8)v15[v16];
    if ( v17 != (unsigned __int8)aEnemyAssassinJ[v16] )
      break;
    if ( v17 == (unsigned __int8)sead::SafeStringBase<char>::cNullChar )
      goto LABEL_37;
    ++v16;
  }
  while ( v16 < 0x80001 );
  bar();
}
```
⬇️
```cpp
// enemy is a sead::SafeString or a derived class
if (enemy == "Enemy_Assassin_Junior")
    foo();
else
    bar();
```

---

##### sead::SafeString::isEmpty

```cpp
if ( *string.cstr == sead::SafeStringBase<char>::cNullChar )
```
⬇️
```cpp
if (string.isEmpty())
```

---

#### ScopedLock

```cpp
sead::CriticalSection::lock(foo);
bar();
sead::CriticalSection::unlock(foo);
```
⬇️
```cpp
{
    auto lock = sead::makeScopedLock(foo);
    bar();
}
```

---

#### Buffer

An sead::Buffer is a non-owning view over a contiguous array of values: it is essentially a wrapper around a raw pointer and a size count.

##### sead::Buffer::allocBufferAssert

In this example, 0x108 is the size of each item.

```cpp
v9 = 0x108LL * (signed int)num_tables;
v10 = is_mul_ok((signed int)num_tables, 0x108uLL) == 0;
v11 = __CFADD__(v9, 8LL);
v12 = v9 + 8;
if ( v11 )
  v13 = 1;
else
  v13 = 0;
if ( (unsigned int)v10 | v13 )
  size = 1LL;
else
  size = v12;
v15 = (char *)operator new[](size, &heap->_, 8u, &std::nothrow);
if ( v15 )
{
    *(_QWORD *)v15 = (signed int)num_tables;
    v16 = (BdropTable *)((char*)v15 + 8);

    // loop over each item and call a constructor
    // note: the constructor may be inlined

    // at the end:
    buffer->size = num_tables;
    buffer->data = v16;
}
```
⬇️
```cpp
buffer->allocBufferAssert(num_tables, heap);
```

Another code pattern with a multiplication that looks different:

```cpp
v13 = operator new[](0x28LL * (unsigned int)count + 8, &heap->_, 8u, &std::nothrow);
if ( v13 )
{
  *v13 = count;
  v14 = (signed __int64)(v13 + 1);
  // loop over each item and call a constructor
  // note: the constructor may be inlined
  // at the end:
  *buffer = count;
  *((_QWORD *)buffer + 1) = v14;
}
```
⬇️
```cpp
buffer->allocBufferAssert(count, heap);
```

If each item is a trivially constructible type (e.g. the buffer stores ints or pointers) then there will be no loop that calls a constructor and the compiler will not store the size of the array in the first 8 bytes of the allocation.

##### sead::Buffer::operator[]

With automatic bounds checks.

```cpp
if ( buffer->size <= i )
    item = buffer->data;
else
    item = buffer->data[i];
```
⬇️
```cpp
item = buffer[i];
```

---

### agl

agl is one of Nintendo's in-house graphics libraries.

#### Parameter utilities

In *Breath of the Wild*, its parameter utilities are heavily used for the game's configuration files.

##### agl::utl::Parameter::init

```cpp
name.vptr = &sead::SafeString::vt;
name.cstr = "Item";
label.vptr = &sead::SafeString::vt;
label.cstr = "表示距離";
meta.vptr = &sead::SafeString::vt;
meta.cstr = (char *)&nullbyte;
agl::utl::ParameterBase::initializeListNode(
  &foo._,
  &name,
  &label,
  &meta,
  bar);
foo.value = default_value;
```
⬇️
```cpp
foo.init(default_value, "Item", "表示距離", bar);
```

---

##### agl::utl::IParameterObj::applyResParameterObj

```cpp
agl::utl::IParameterObj::applyResParameterObj_(foo, 0, bar, 0LL, 0.0, 0LL);
```
⬇️
```cpp
foo.applyResParameterObj(bar);
```

---

##### agl::utl::ResParameterArchive::getRootList

```cpp
agl::utl::ResParameterArchive::ResParameterArchive(&archive, data);
root.ptr = (agl::utl::ResParameterListData *)((char *)&archive.ptr[1] + (unsigned int)archive.ptr->rootOffsetAfterHeader);
```
⬇️
```cpp
agl::utl::ResParameterArchive archive{data};
auto root = archive.getRootList();
```

---

##### Getting ResParameterObj or ResParameterList

```cpp
key.vptr = &sead::SafeString::vt;
key.cstr = "InvalidWeathers";
key_hash = agl::utl::ParameterBase::calcHash(&key);
idx = agl::utl::ResParameterList::searchObjIndex(&foo, key_hash);
if ( idx == 0xFFFFFFFF )
{
  obj = 0LL;
}
else
{
  obj = (__int64)v30.ptr + 8 * idx + 4 * (unsigned __int16)v30.ptr->objOffsetNum;
  if ( obj )
  {
    bar();
  }
}
```
⬇️
```cpp
const auto obj = agl::utl::getResParameterObj(foo, "InvalidWeathers");
if (obj.ptr())
    bar();
```

## C++ features

### Classes

#### Constructors

If you see a function that modifies the vtable pointer and/or calls a lot of other constructors, chances are that you are dealing with a constructor.

In C++, most of the code in constructor functions tends to be automatically generated by the compiler. For example, the following function:

```cpp
void __fastcall ksys::res::Handle::Handle(ksys::res::Handle *this)
{
  this->mFlags = 1;
  this->mStatus = 0;
  this->mUnit = 0LL;
  this->vtable = &ksys::res::Handle::vt;
  ksys::util::ManagedTaskHandle::ManagedTaskHandle(&this->mTaskHandle);
  this->field_40 = 0LL;
  this->field_48 = 0LL;
}
```

is automatically generated based on the class definition:

```cpp
// irrelevant details were simplified or removed
struct Handle {
    u8 mFlags = 1;
    Status mStatus = Status::_0;
    ResourceUnit* mUnit = nullptr;
    util::ManagedTaskHandle mTaskHandle;
    sead::ListNode mListNode;
};
```

Note that the sead::ListNode constructor was inlined here, and *that* constructor was also automatically generated by the compiler:

```cpp
class ListNode
{
public:
    // ...
    ListNode* mPrev = nullptr;
    ListNode* mNext = nullptr;
};
```
---

#### Member functions and member variables

C++ member functions are called as if they had the `this` pointer as the first argument.

```cpp
sead::CriticalSection::lock(some_variable);
ksys::res::ResourceUnit::attachHandle(unit, handle);
```
⬇️
```cpp
some_variable->lock();
unit->attachHandle(handle);
```

Member variables are accessed using the `this` pointer. In C++, explicitly writing `this` is usually unnecessary:

```cpp
if ( this->mNumCaches <= idx )
    cache = this->mCaches;
else
    cache = &this->mCaches[idx];
```
⬇️
```cpp
if (mNumCaches <= idx)
    cache = mCaches;
else
    cache = &mCaches[idx];
```
---

### Custom operator new

sead defines several custom allocation functions. You should `#include <basis/seadNew.h>` to ensure they are used for heap allocations.

```cpp
void* ptr = ::operator new(SOME_SIZE_HERE, heap, 8u);
SomeClass::SomeClass(ptr);  //< constructor call
```
⬇️
```cpp
auto* ptr = new (heap) SomeClass;
```

Sometimes, a non-throwing overload of `operator new` is used:

```cpp
void* ptr = ::operator new(SOME_SIZE_HERE, heap, 8u, &std::nothrow);
SomeClass::SomeClass(ptr);  //< constructor call
```
⬇️
```cpp
auto* ptr = new (heap, std::nothrow) SomeClass;
```

This also applies for `new[]`.
