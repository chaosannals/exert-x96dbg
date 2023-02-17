add_executable(crackcmd)

option(CRACKCMD_VS_LINK_STATIC_MT "crackcmd static link mt." ON)

set_target_properties(
    crackcmd
    PROPERTIES
    CXX_STANDARD 20
)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY git@github.com:p-ranav/argparse.git
    GIT_TAG v2.9
)
FetchContent_MakeAvailable(argparse)

if (WIN32)
   if (MSVC)
      # æ≤Ã¨‘À––ø‚ MT
      if (CRACKCMD_VS_LINK_STATIC_MT)
          set_target_properties(
              crackcmd
              PROPERTIES
              MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
          )
         message(STATUS "crackcmd msvc MT")
      endif()

      # ∆Ù”√ MASM ª„±‡
      enable_language(ASM_MASM)
      if (NOT CMAKE_ASM_MASM_COMPILER_WORKS)
        message(STATUS "not found MASM.")
      endif()
   else()
      # ∆Ù”√ Linux ª„±‡
      enable_language(ASM)
   endif()
endif()

target_include_directories(
    crackcmd
    PRIVATE
    "${argparse_SOURCE_DIR}/include"
)

target_sources(
    crackcmd
    PRIVATE
    # "src/peb.asm"
    "src/main.cpp"
)