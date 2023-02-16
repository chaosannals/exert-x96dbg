add_executable(cracksehw WIN32)

option(CRACKSEHW_VS_LINK_STATIC_MT "cracksehw static link mt." ON)

set_target_properties(
    cracksehw
    PROPERTIES
    CXX_STANDARD 20
)

if (WIN32)
   if (MSVC)
      # æ≤Ã¨‘À––ø‚ MT
      if (CRACKSEHW_VS_LINK_STATIC_MT)
          set_target_properties(
              cracksehw
              PROPERTIES
              MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
          )
         message(STATUS "cracksehw msvc MT")
      endif()
   endif()
endif()

target_sources(
    cracksehw
    PRIVATE
    "src/main.cpp"
)
