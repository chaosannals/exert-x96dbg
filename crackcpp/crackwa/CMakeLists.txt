add_executable(crackwa WIN32)

option(CRACKWA_VS_LINK_STATIC_MT "crackwa static link mt." ON)

set_target_properties(
    crackwa
    PROPERTIES
    CXX_STANDARD 20
)

if (WIN32)
   if (MSVC)
      # 指定 Unicode
      target_compile_definitions(
          crackwa
          PUBLIC
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

target_sources(
    crackwa
    PRIVATE
    "src/main.cpp"
)
