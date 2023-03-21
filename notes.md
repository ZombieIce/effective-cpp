## Deducing Types
#### Item 1: Understand template type deduction
1. During template type deduction, arguments that are references are treated as non-references, i.e., their reference-ness is ignored.
2. When deducing types for universal reference parameters, lvalue arguments get special treatment.
3. When deducing type for by-value paramenters, const and/or volatile arguments are treated as non-const and non-volatile.
4. During template type deduction, arguments that are array or function names decay to pointers, unless they’re used to initialize references.
#### Item 2: Understand auto type deduction
1. auto type deduction is usually the same as template type deduction, but auto type deduction assumes that a braced initializer represents a std::initializer\_list, and template type deduction doesn’t.
2. auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
#### Item 3: Understand decltype
1. decltype almost always yields the type of a variable or expression without any modifications.
2. For lvalue expressions of type T other than names, decltype always reports a type of T&.
3. C++14 supports decltype(auto), which, like auto, deduces a type from its initializer, but it performs the type deduction using the decltype rules.
#### Item 4: Know how to view deduced types
1. Deduced types can often be seen using IDE editors, compiler error messages, and the Boost TypeIndex library.
2. The results of some tools may be neither helpful nor accurate, so an under‐ standing of C++’s type deduction rules remains essential.
## Auto
#### Item 5: Prefer auto to explicit type declarations
1. auto variables must be initialized, are generally immune to type mismatches that can lead to portability or efficiency problems, can ease the process of refactoring, and typically require less typing and varivable with explicitly specified types.
2. auto-typed varibles are subject to the pitfalls described in Item 2 and Item 6.
#### Item 6: Use the explicitly typed initializer idiom when auto deduces undesired types
1. "Invisible" proxy types can cause auto to deduce the "wrong" type for an initializing expression.
2. The explicitly typed initializer idiom forces auto to deduce the type you want it to have.
## Moving to Modern C++
#### Item 7: Distinguish between () and {} when creating objects
1. Braced initialization is the most widely usable initialization syntax, it prevents narrowing conversions, and it’s immune to C++’s most vexing parse.
2. During constructor overload resolution, braced initializers are matched to std::initializer\_list parameters if at all possible, even if other constructors offer seemingly better matches.
3. An example of where the choice between parentheses and braces can make a significant difference is creating a std::vector<numeric type> with two arguments.
4. Choosing between parentheses and braces for object creation inside templates can be challenging.
#### Item 8: Prefer nullptr to 0 and NULL.
1. Prefer nullptr to 0 num NUll.
2. Avoid overloading on integral and pointer types.
#### Item 9: Prefre alias declarations to typedefs.
1. typedefs don't support templatization, but alias declarations do.
2. Alias templates avoid the "::type" suffix and, in templates, the "typename" prefix often required to refer to typedefs.
3. C++14 offers alias templates for all the C++11 type traits transformations.
#### Item 10: Prefer scoped enums to unscoped enums.
1. C++98-style enums are now known as unscoped enums.
2. Enumerators of scoped enums are visible only within the enum. They convert to other types only with a cast.
3. Both scoped and unscoped enums support specification of the underlying type. The default underlying type for scoped enums is int. Unscoped enums have no default underlying type.
4. Scoped enums may always be forward-declared. Unscoped enums may be forward-declared only if their declaration specifies an underlying type.
#### Item 11: Perfer deleted functions to private undefined ones.
1. Prefer deleted functions to private undefined ones.
2. Any function may be deleted, including non-member functions and template instantiations.
#### Item 12: Declare overriding functions override.
1. Declare overriding functions override.
2. Member function reference qualifiers make it possible to treat lvalue and rvalue objects(*this) differently.
#### Item 13: Prefer const_iterators to iterators
1. Prefer const_iterators to iterators.
2. In maximally generic code, prefer non-member versions of begin, end, rbegin, etc., over their member function counterparts.
#### Item 14: Declare functions noexcept if they won't emit exceptions
1. noexcept is part of a function's interaface, and that means that callers may depend on it.
2. noexcept functions are more optimizable than non-noexcept functions.
3. noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
4. Most functions are exception-neutral rather than noexcept.
#### Item 15: Use constexpr whenever possible


