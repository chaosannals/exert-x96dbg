add_executable(crackcmd)

option(CRACKCMD_VS_LINK_STATIC_MT "crackcmd static link mt." ON)

set_target_properties(
    crackcmd
    PROPERTIES
    CXX_STANDARD 17
)

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
   endif()
endif()

target_sources(
    crackcmd
    PRIVATE
    "src/main.cpp"
)