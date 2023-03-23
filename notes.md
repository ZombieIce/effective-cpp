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
1. constexpr objects are const and are initialized with values known
   during compilation.
2. constexpr functions can produce compile-time results when called
   with arguments whose values are known during compilation.
3. constexpr objects and functions may be used in a wider range of
   contexts than non-constexpr objects and functions.
4. constexpr is part of an object's or function's interface.
#### Item 16: Make const member functions thread safe.
1. Make const member functions thread safe unless you're certain
   they'll never be usded in a concurrent context.
2. Use of std::atomic varibles may offer better performance than a
   mutex, but they're suited for manipulation of only a single varible
   or memory location.
#### Item 17: Understand special member function generation
1. The special member functions are those compilers may generate on
   their own; default constructor, destructor, copy operations, and
   move operations.
2. Move operations are generated only for classes lacking explicitly
   declared move operations, copy operations, and a destructor.
3. The copy constructor is generated only for classes lacking an
   explicitly declared copy constructor, and it's deleted if a move
   operation is declared. The copy assignment operator is generated
   only for classes lacking an explicitly declared copy assignment
   operator, and it's deleted if a move operation is declared.
## Smart Pointers
在C++11中通过引入智能指针的概念，使得C++程序员不需要手动释放内存
- 原始指针 raw_ptr
- 独占指针 unique_ptr
- 计数指针 shared_ptr
- weak_ptr
智能指针与Rust的内存安全
- 智能指针只解决了一部分问题，即独占/共享所有权指针的释放、传输
- 智能指针没有从根本上解决C++内存安全问题，不加以注意依然会造成内存安全问题
#### Item 18: Use std::unique\_ptr for exclusive-ownership resource management
- 在任何给定的时刻，只能有一个指针管理内存
- 当指针超出作用域时，内存将自动释放
- move-only 不可以copy
- 三种创建方式
  - 通过已有的裸指针创建
  - 通过new来创建
  - 通过std::make_unique创建（推荐）
- unique_ptr 可以通过get() 获取
- unique_ptr 实现了 -> 与 *
- 注意事项
  - Passing by value
    - 需要使用 std::move 来转移内存拥有权
    - 如果参数直接传入 std::make_unique语句 自动转换为move
  - passing by reference
    - 如果设置参数为const则不能改变指向 reset()
    - reset() 方法为智能指针清空方法
  - Return by value
    - 指向一个local object
    - 可以用作链式函数
- 不能将shared\_ptr 转换为 unique\_ptr
- 将你的函数返回unique\_ptr 是一种常见的设计模式，这样可以提高代码的复用度
1. std::unique_ptr is a small, fast, move-only smart pointer for
   managing resources with exclusive-ownership semantics.
2. By default, resource destruction takes via delete, but custom
   deleters can be specified. Stateful deleters and function pointers
   as deleters increase the size of std::unique_ptr objects.
3. Converting a std::unique_ptr to a std::shared_ptr is easy.
#### Item 19: Use std::shared\_ptr for shared-ownership resource management
- shared_ptr 计数指针又称为共享指针
- 与 unique_ptr 不同的是它是可以共享数据的
- shared_ptr 创建了一个计数器与类对象所指的内存相关联 copy +1 delete
  - api为use_count()
- shared_pty passed by value
  - copy
  - 函数内部计数器加1
- shared_ptr passd by ref
  - const 表示不可改变指向
- returning by value
  - 链式调用
1. std::shared_ptrs offer convenience approaching that of gargage
   collection for the shared liftime management of arbitrary
   resrouces.
2. Compared to std::unique_ptr, std::shared_ptr objects are typically
   twice as big, incur overhead for control blocks, and require atomic
   reference count manipulation.
3. Default resource destruction is via delete, but custom deleters are
   supported. The type of the deleter has no effect on the type of the
   std::shared_ptr.
4. Avoid creating std::shared_ptrs from variables of raw pointer type.
#### Item 20: Use std::weak\_ptr for std::shared\_ptr-like pointers that can dangle.
- weak_ptr 并不拥有所有权
- 并不能调用->和解引用*
- A类中有一个需求需要存储其他A类对象的信息
- 如果使用shared\_ptr, 那么在销毁时会遇到循环依赖问题
- 所以这里需要一个不需要拥有所有权的指针来标记该同类对象
  - weak\_ptr 可以通过lock()函数来提升为 shared\_ptr(类型转换)
1. Use std::weak\_ptr for std::shared\_ptr-like pointers that can
   dangle.
2. Potential use cases for std::weak\_ptr include caching, observer
   lists, and the prevention of std::shared_ptr cycles.
#### Item 21: Prefer std::make\_unique and std::make\_shared to direct use of new.
1. Compared to direct use of new, make functions eliminate source code
   duplication, imporve exception safety, and, for std::make\_shared
   and std::allocate\_shared, generate code that's smaller and faster.
2. Situations where use of make functions is inappropriate include the
   need to specify custom deleters and a desire to pass braced
   initializers.
3. For std::shared\_ptrs, addtional situations where make functions may
   be ill-advised include (1) classes with custom memory management
   and (2) systems with memory concerns, very large objects, and
   std::weak\_ptrs that outlive the corresponding std::shared_ptrs.
#### Item 22: When using the Pimpl, define special member functions in the implementation file.
pointer to implementation

1. Th Pimpl Idiom decreases build times by reducing compilation
   dependencies between class clients and class implementations.
2. For std::unique\_ptr pIml pointers, declare special member functions
   in the class header, but implement them in the implementation file.
   Do this even if the default function implementations are
   acceptable.
3. The above advise applies to std::unique\_ptr, but not to
   std::shared\_ptr.
## Rvalue References, Move Semantics, and Perfect Forwarding
#### Item 23: Understand std::move and std::forward
1. std::move performs an unconditional cast to an rvalue. In and of
   itself, it doesn't move anything.
2. std::forward casts its argument to an rvalue only if that argument
   is bound to an rvalue.
3. Neither std::move nor std::forward do anything at runtime.
#### Item 24: Distinguish universal references from rvalue reference
1. if a function template parameter has type T&& for a deduced type T,
   or if an object is declared using auto&&, the parameter or object
   is a universal reference.
2. if the form of the type declaration isn't precisely type&&, or if
   type deduction does not occur, type&& denotes an rvalue reference.
3. Universal references correspond to rvalue references if they're
   initialized with rvalues. They correspond to lvalue references if
   they're initialized with lvalues.
#### Item 25: Use std::move On rvalue references, std::forward on universal references.
1. Apply std::move to rvalue references and std::forward to universal
   references the last time each is used.
2. Do the same thing for rvalue references and universal references
   being returned from functions that return by value.
3. Never apply std::move or std::forward to local objects if they
   would otherwise be eligible for the return value optimization.
#### Item 26: Avoid overloading on universal references.
1. Overloading on universal references almost always leads to the
   universal reference overload being called more frequently than
   expected.
2. Perfect-forwarding constructors are especially problematic, because
   they're typically better matches than copy constructors for
   non-const lvalues, and they can hijack derived class calls to base
   class copy and move constructors.
#### Item 27: Familiarize yourself with alternatives to overloading on universal references.
1. Alternatives to the combination of universal references and
   overloading include the use of distinct function names, passing
   parameters by lvalue-reference-to-const, passing parameters by
   value, and using tag dispatch.
2. Constraining templates via std::enable\_if permits the use of
   universal references and overloading together, but it controls the
   conditions under which compilers may use the universal reference
   overloads.
3. Universal reference parameters often have efficiency advantages,
   but they typically have usability disadvantages.
#### Item 28: Understand reference collapsing.
1. Reference collapsing occurs in four contexts: template instantiation, auto type generation, creation and use of typedefs and alias declarations, and decltype.
2. When compilers generate a reference to a reference in a reference collapsing context, the result becomes a single reference. If either of the original refer‐ ences is an lvalue reference, the result is an lvalue reference. Otherwise it’s an rvalue reference.
3. Universal references are rvalue references in contexts where type deduction distinguishes lvalues from rvalues and where reference collapsing occurs.
#### Item 29: Assume that move operations are not present, not cheap, and not used
1. Assume that move operations are not present, not cheap, and not used.
2. In code with known types or support for move semantics, there is no need for assumptions.
#### Item 30: Familiarize yourself with perfect forwarding failure cases.
1. Perfect forwarding fails when template type deduction fails or when it deduces the wrong type.
2. The kinds of arguments that lead to perfect forwarding failure are braced ini‐ tializers, null pointers expressed as 0 or NULL, declaration-only integral const static data members, template and overloaded function names, and bitfields.
## Lambda Expressions
#### Item 31: Avoid default capture modes.
1. Default by-reference capture can lead to dangling references.
2. Default by-value capture is susceptible to dangling pointers
   (especially this), and it misleadingly suggests that lambdas are
   self-contained.
#### Item 32: Use init capture to move objects into closures.
1. Use C++14's init capture to move objects into closures.
2. In C++11, emulate init capture via hand-written classes or
   std::bind
#### Item 33: Use decltype on auto&&parameters to std::forward them.
1. Use decltype on auto&& parameters to std::forward them.
#### Item 34: Prefer lambdas to std::bind.
1. Lambdas are more readable, more expressive, and may be more
   efficient than using std::bind.
2. In C++11 only, std::bind may be useful for implementing move
   capture or for binding objects with templatized function call
   operations.
## Chapter 7 The Concurrency API
#### Item 35: Prefer task-based programming to thread-based.
1. the std::thread API offers no direct way to get return values from
   asynchronously run functions, and if those function throw, the
   program is terminated.
2. Thread-based programming calls for manual management of thread
   exhaustion, oversubscription, load balancing, and adaptation to new
   platforms.
3. Task-based programming via std::async with the default launch
   policy handles most of these issues for you.
#### Item 36: Specify std::launch::async if asynchronicity is essential.
1. The default launch policy for std::async permits both asynchronous and synchronous task execution.
2. This flexibility leads to uncertainty when accessing thread_locals, implies that the task may never execute, and affects program logic for timeout-based wait calls.
3. Specify std::launch::async if asynchronous task execution is essential.
#### Item 37: Make std::threads unjionable on all paths.
1. Make std::threads unjoinable on all paths.
2. join-on-destruction can lead to difficult-to-debug performance
   anomalies.
3. detach-on-destruction can lead to difficult-to-debug undefined
   behavior.
4. Declare std::thread objects last in lists of data members.
#### Item 38: Be aware of varying thread handle destructor
