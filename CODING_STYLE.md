Philosophy

This codebase follows a C with Classes approach: C semantics with carefully selected C++ features.
The goal is explicitness, predictability, auditability, and mechanical sympathy.

Modern C++ idioms are intentionally avoided.

If something looks “clever”, it is probably wrong.
---

Language & Runtime Model
- Language: C++ (freestanding mindset)
- No C++ standard library (no `std::` of any kind)
- No exceptions
- No RTTI
- No references
- No smart pointers
- No implicit ownership or lifetime semantics

---

Permitted Language Features
- Classes with constructors/destructors only when they cannot fail
- Abstract classes strictly used as interfaces
- Shallow, purpose-driven templates
- `constexpr` for constants and simple compile-time values
- Plain `enum`
- `goto` (with restrictions)

---

Prohibited Language Features
- C++ standard library
- References
- Smart pointers
- Exceptions
- RTTI
- `enum class`
- Template metaprogramming
- SFINAE, concepts, CRTP, policy-based design

---

Memory Management
- Memory allocation is performed via:
  - `malloc` / `free`, or
  - explicit virtual memory primitives (`mmap`, `VirtualAlloc`, etc.)
- RAII is allowed only when constructors and destructors:
  - cannot fail
  - do not allocate
  - do not perform I/O
- Ownership must always be explicit and visible

---

File Naming

| Purpose | Extension |
|---------|-----------|
| Headers | .h |
| Implementation | .cc |
| Inline / shared implementation | .i |


---

Include Rules
- Prefer angle brackets `<>`
- Always include headers via their full logical path
- Relative includes are forbidden

```cpp
#include <xenon/platform/x11/window.h>
```


---

Naming Conventions

Types

All types use Ada-Pascal-Case with module qualification:

```
<Module>_<Type>
```

Examples:

```
Xenon_DisplayDriver
Xenon_Error
Njord_Allocator
```

---

Functions
- All important functions use snake_case
- Applies to:
  - global functions
  - static
  - inline
  - static inline

Required format:

```
<module>_<action>
```

Examples:

```
xenon_get_display
xenon_create_window
xenon_init_allocator
```


---

Naming: Conciseness

Names must be short, precise, and non-redundant.

Avoid encoding execution context or implementation details.

```cpp
// Forbidden
retrieve_active_clients_from_connected_db

// Preferred
retrieve_clients
```


---

Global Symbols
- Global variables use SCREAMING_CASE
- No prefixes such as `g_`, `k`, `s_`
- `GLOBAL_` prefix is allowed and encouraged when it improves clarity

Examples:

```
GLOBAL_LOOKUP
TYPE_REGISTRY
GLOBAL_TYPE_REGISTRY
```

---

Enumerations
- Use plain `enum`
- No `enum class`
- Enum variants use SCREAMING_CASE
- Variants must be fully qualified

```cpp
enum Xenon_Display_Error {
    XENON_DISPLAY_ERROR_NONE = 0,
    XENON_DRIVER_X11_COULD_NOT_CONNECT,
};
```

---

Integer Types & Narrowing
- Always use fixed-width types from `<cstdint>`
- `int`, `long`, `unsigned`, and `size_t` are forbidden (except ABI boundaries)
- Choose the smallest correct type
- All narrowing must be explicit and intentional

---

Type Aliases
- Prefer `typedef`
- Use `using` only when `typedef` is syntactically impossible
- No standard-library type traits

---

Templates

Templates are allowed only when unavoidable.

Allowed
- Shallow templates with concrete intent
- Templates that reduce duplication and could be replaced by codegen

Forbidden
- Nested templates
- Metaprogramming
- Type-level logic
- Clever overload tricks

If a template cannot be understood without expanding it mentally, it is rejected.

---

Structures
- Structs should be POD whenever possible
- Follow Rule of Zero
- No access specifiers
- No empty or trivial constructors/destructors

---

Classes & Interfaces
- All members are visible
- Abstract classes are used only as interfaces
- Interface inheritance depth must not exceed 2
- Prefer explicit lifecycle functions:

```
Xenon_Type_init
Xenon_Type_deinit
```


---

POD Initialization Macros

If POD initialization is trivial and cannot fail, a macro must be used.

```cpp
#define XENON_POINT_INIT { 0, 0 }
```

- Macros must not allocate
- Macros must not contain logic

Placement initialization is explicitly endorsed.

---

Operator Overloading
- Strongly discouraged
- Allowed only for obvious, mathematical semantics
- Prefer explicit named functions

---

Control Flow

Control flow must be simple, linear, and shallow.

Nesting Rules
- Nesting of `if`, `for`, `while`, `switch` must be minimal
- Nest only when the task fundamentally requires it
- Prefer early return over defensive nesting

---

Early Return Policy
- Functions should return success by default
- Validate inputs at the top
- Exit immediately on failure
- Avoid wrapping the happy path in conditionals

---

goto Rules
- `goto` is allowed
- Only forward jumps are permitted
- Upward jumps are forbidden
- Preferred uses:
  - exiting loops
  - centralized cleanup
  - skipping invalid paths

Labels must be concise:

```
out
fail
cleanup
```

---

Constness, Copies, and Lifetime

Trivially Copyable Types
- If a value is trivially copyable and inexpensive:
  - pass by value
  - Do not introduce indirection unnecessarily

---

Non-Modifying Pointer Parameters
- If a pointer parameter must not modify its target:
  - it must be marked `const`
  - Missing `const` is a correctness bug

---

Output Parameters
- Output parameters are never `const`
- Output parameters always appear last
- Single output parameter uses name `out`
- Multiple outputs use `out_<name>`

---

Lifetime Rules
- Passing by value implies no lifetime dependency
- Passing by pointer implies validity for call duration
- Extended lifetime requirements must be documented

---

Comments
- Comments are minimal
- No comments inside function bodies
- Exception: safety annotations only

```cpp
// SAFETY: deref of opaque pointer is safe; validated during init
```

- Comments describe what and why, not how

---

Error Handling
- No exceptions
- All fallible functions return an error code
- No hidden control flow
- Errors are explicit and documented

---

Formatting Summary

| Element | Style |
|---------|-------|
| Types | Ada-Pascal-Case |
| Functions | snake_case |
| Globals | SCREAMING_CASE |
| Enums | SCREAMING_CASE |
| Files | lowercase |
| Init / deinit | Type_init / Type_deinit |


---

Best Practices
1. Prefer explicit over implicit
2. Keep ownership visible
3. Minimize abstraction
4. Avoid cleverness
5. Validate inputs at API boundaries
6. Keep templates boring
7. Document safety assumptions
8. Prefer POD over behavior
9. Reject “modern C++ style” by default