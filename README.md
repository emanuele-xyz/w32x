# w32x

Compiles with all warnings enabled, except for:
- [C4514](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4514?view=msvc-170): unreferenced inline function has been removed
- [C4710](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4710?view=msvc-170): the specified function was marked for inline expansion, but the compiler didn't inline the function
- [C4711](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-170): the compiler performed inlining on the given function, although it was not marked for inlining
- [C5045](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5045?view=msvc-170): compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
