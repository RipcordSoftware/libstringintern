# libstringintern
A C++ library for [interning][string-interning] strings to save heap space. Smaller heaps generally mean faster applications due to cache locality and less swapping to disk.

## Use case
If you have an in-memory database with 100 million customer records with associated address details then you probably have 100 million state and country strings associated with those records. That will use a lot of memory. 

When strings are interned you only ever have one instance of the string plus a reference instance per record which is 4 bytes in size.

### Let's do the maths
* 100m * 'Mississippi\0' = **1144MB**
* 1 * 'Mississippi\0' = 12B, 100m * 4B = **381MB**

[string-interning]: https://en.wikipedia.org/wiki/String_interning
