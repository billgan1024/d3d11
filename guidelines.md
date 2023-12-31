## C++ Notes
- C arrays implicitly cast to pointers via a conversion to a pointer to the first element. But 
- for some reason you can't return a C array of constant size from a function. You have to return a pointer.
- C arrays also define a type: `T a[n]` defines a new type representing `n` contiguous `T`s. By applying 
this logic recursively, we get multidimensional arrays.

## C++ Guidelines
- Always initialize variables (including global ones) for consistency.
- Use `nullptr` instead of `NULL` since `nullptr` is a pointer type according to the compiler.
- Only use the following forms for initialization:
  - `int x = 0; float f = 0.0` (for simplicity, use any numeric literal for any numeric type. 
  recall that integral types convert between each other by shrinking/expanding the most significant part,
  and that signed <-> unsigned preserves bit pattern)
  - `vector<int> v = vector<int>{1, 2, 3};` for constructing via an initializer list. For some reason,
  `{1, 2, 3}` makes the compiler unable to deduce the type of the
  initializer list in certain contexts (e.g. with operator overloading). Note that C-style arrays cannot be
  initialized this way, so don't use them in this context.
  - `A a = A(...);` for accessing a constructor. This avoids "most vexing parse" and this is also the only 
  good way to initialize a variable in HLSL.
  - `A a; memset(&a, 0, sizeof(a));` for initializing a POD (no constructors/destructors). This is the only
  sane way to initialize a struct. Designated initializers are garbage.
- Avoid integer division because it's not the same as floating point (real) division.
- Only use `a % b` when `b` is positive and an integral type.
- Syntax for compile-time variadic functions:
  ```cpp
  template <class T, class... A>
  void printc(T t, A... a);

  void printc();
  
  #include "misc.tpp"
  ```
  Remember that `misc.tpp` holds the implementation of templates since they must be in the header file. 
  `printc` is in a cpp file.