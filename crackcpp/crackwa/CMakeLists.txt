add_executable(crackwa WIN32)

option(CRACKWA_VS_LINK_STATIC_MT "crackwa static link mt." ON)

set_target_properties(
    crackwa
    PROPERTIES
    CXX_STANDARD 20
)

# 启用 MASM 汇编
enable_language(ASM_MASM)
if (NOT CMAKE_ASM_MASM_COMPILER_WORKS)
    message(STATUS "not found MASM.")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "is Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "is Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "is MacOS")
endif()

if (WIN32)
   if (MSVC)
      # 指定 Unicode
      target_compile_definitions(
          crackwa
          PUBLIC
          -DCRACKWA_LV=2 # 加 -D 前缀可以
          CRACKWA_TIP="crack windows app" # 不加 -D 也可以
          CRACKWA_TOKEN
          -DUNICODE
          -D_UNICODE
      )

      # 静态运行库 MT
      if (CRACKWA_VS_LINK_STATIC_MT)
          set_target_properties(
              crackwa
              PROPERTIES
              MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
          )
         message(STATUS "crackwa msvc MT")
      endif()
   endif()
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "inline asm")
    set(PEB_ASM_FILES "")
else()
    # 只是 VS 有效
    if (CMAKE_CL_64)
        message(STATUS "is 64bit")
        set(PEB_ASM_FILES "src/peb_x64.asm")
    else()
        message(STATUS "is 32bit")
        set(PEB_ASM_FILES "src/peb_x86.asm")
    endif()
endif()

target_sources(
    crackwa
    PRIVATE
    "${PEB_ASM_FILES}"
    "src/main.cpp"
 "src/peb.h" "src/winter.h")
