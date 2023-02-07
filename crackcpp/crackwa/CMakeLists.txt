add_executable(crackwa WIN32)

option(CRACKWA_VS_LINK_STATIC_MT "crackwa static link mt." ON)

set_target_properties(
    crackwa
    PROPERTIES
    CXX_STANDARD 20
)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "is Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "is Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "is MacOS")
endif()

if (CMAKE_CL_64)
    message(STATUS "is 64bit")
else()
    message(STATUS "is 32bit")
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

target_sources(
    crackwa
    PRIVATE
    "src/main.cpp"
)
