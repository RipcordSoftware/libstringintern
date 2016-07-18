[![Build Status](https://travis-ci.org/RipcordSoftware/libstringintern.svg)](https://travis-ci.org/RipcordSoftware/libstringintern)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/libstringintern/badge.svg?branch=master&service=github)](https://coveralls.io/github/RipcordSoftware/libstringintern?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

# libstringintern
A thread safe lock free C++ library for [interning][string-interning] strings to save heap space. Smaller heaps generally mean faster applications due to cache locality and less swapping to disk. The other upside is you can store more stuff in RAM.

## Use case
You have an in-memory database with 100 million customer records with associated address details. You therefore have 100 million state and country strings associated with those records. That will use a lot of memory. 

When strings are interned you only ever have one instance of the string plus a reference instance per record which is 4 bytes in size.

### Let's do the math(s)
* 32bit: 100m * 'Mississippi\0' = 1144MB, 100m * 4B = 381MB, total = **1525MB**
* 64bit: 100m * 'Mississippi\0' = 1144MB, 100m * 8B = 762MB, total = **1907MB**
* Interned: 1 * 'Mississippi\0' = 12B, 100m * 4B = **381MB**

This example is for a fairly short string, but the saving is still valuable. Larger strings have an even bigger pay-off.

## How it works
* Interned strings are stored in pages, grouped by string size, a bit like [tcmalloc][tcmalloc]
* Pages are 2MB in size to take advantage of [THP][thp]
* Each string is hashed using [XX64][xx64] with the low order bytes used as an index into the page
* If the index refers to a location in the page that is free the string and hash are committed to the page and the caller gets a *reference* to the string
* If the index is already taken then we compare the hashes and if they match we return a reference to the entry
* If the hashes did not match then allocate a new page and add the string and hash returning the string reference
* The host application turns the reference into a real pointer to use the string, a bit like `std::weak_ptr`
* References are 32bit values made up from PAGE(16):INDEX(16). On 64bit systems these use half the storage space of a pointer.
* Interned strings are immutable

## Code example
```c++
  StringIntern intern;
  auto ref1 = intern.Add("Mississippi");
  std::cout << intern.ToString(ref1) << std::endl;
  
  auto ref2 = intern.Add("Mississippi");
  std::cout << ref1 == ref2 ? "Match" : "Doesn't match" << std::endl;
```

## Testing
We have tested extensively on Intel, PPC and ARMv7. If you have another system you'd like us to test with please let us know.

[string-interning]: https://en.wikipedia.org/wiki/String_interning
[tcmalloc]: http://goog-perftools.sourceforge.net/doc/tcmalloc.html
[thp]: https://www.kernel.org/doc/Documentation/vm/transhuge.txt
[xx64]: https://github.com/Cyan4973/xxHash
