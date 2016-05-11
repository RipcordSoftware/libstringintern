# libstringintern
A C++ library for [interning][string-interning] strings to save heap space. Smaller heaps generally mean faster applications due to cache locality and less swapping to disk. The other upside is you can store more stuff in RAM.

> libstringintern is a work-in-progress. Almost everything can change so don't believe a thing written here until Travis passes the units.

## Use case
You have an in-memory database with 100 million customer records with associated address details. You therefore have 100 million state and country strings associated with those records. That will use a lot of memory. 

When strings are interned you only ever have one instance of the string plus a reference instance per record which is 4 bytes in size.

### Let's do the maths
* 100m * 'Mississippi\0' = **1144MB**
* 1 * 'Mississippi\0' = 12B, 100m * 4B = **381MB**

This example is for a fairly short string, but the saving is still valuable. Larger strings have a much bigger pay-off.

## How it works
* Interned strings are stored in pages, grouped by string size, a bit like [tcmalloc][tcmalloc]
* Pages are 2MB in size to take advantage of [THP][thp]
* Each string is hashed using [XX64][xx64] with the low order bytes used as an index into the page
* If the index refers to a location in the page that is free the string and hash are committed to the page and the caller gets a *reference* to the string
* If the index is already taken then we compare the hashes and if they match we return a reference to the entry
* If the hashes did not match then allocate a new page and add the string and hash returning the string reference
* The host application turns the reference into a real pointer to use the string, a bit like `std::weak_ptr`
* Interned strings are immutable

## Made up code example
There is no code **yet**, but here is an example anyway:
```c++
  auto strRef1 = StringIntern::Add("Mississippi");
  std::cout << StringIntern::String(strRef1) << std::endl;
  
  auto strRef2 = StringIntern::Add("Mississippi");
  std::cout << strRef1 == strRef2 ? "Match" : "Doesn't match" << std::endl;
```

[string-interning]: https://en.wikipedia.org/wiki/String_interning
[tcmalloc]: http://goog-perftools.sourceforge.net/doc/tcmalloc.html
[thp]: https://www.kernel.org/doc/Documentation/vm/transhuge.txt
[xx64]: https://github.com/Cyan4973/xxHash
