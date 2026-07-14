#ifdef thiscall
#undef thiscall
#endif

//PLACEHOLDER THOSE DEFINITIONS ARE WRONG

#if GCC_COMPAT
#define cdecl __attribute__((cdecl))
#define stdcall __attribute__((stdcall))
#define fastcall __attribute__((fastcall))
#define thiscall __attribute__((thiscall))
#elif MSVC_COMPAT || CLANG_COMPAT

#define stdcall __stdcall
#define fastcall __fastcall
#define thiscall __thiscall
#else
#define cdecl
#define stdcall 
#define fastcall
#define thiscall
#endif

#define noinline [[clang::noinline]]
#define forceinline [[clang::always_inline]]
#define _BYTE BYTE
#define PI 3.14159265359
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"


template <typename T>
static inline constexpr T garbage_value(void) {
	T garbage;
	return garbage;
}

template<typename T1, typename T2>
forceinline static constexpr T1 bitcast(const T2& value) {
	return __builtin_bit_cast(T1, value);
}

#define GARBAGE_VALUE(type) garbage_value<type>()
#define GARBAGE_ARG(type) GARBAGE_VALUE(type)

#pragma clang diagnostic pop


#define UNUSED_DWORD (GARBAGE_ARG(int))
#define UNUSED_FLOAT (GARBAGE_ARG(float))

