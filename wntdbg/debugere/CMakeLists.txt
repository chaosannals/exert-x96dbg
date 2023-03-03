option(DEBUGERE_VS_LINK_STATIC_MT "static link mt." ON)

set(ELEMENTS_APP_PROJECT "debugere")
set(ELEMENTS_APP_TITLE "debugere")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2023")
set(ELEMENTS_APP_ID "chaosannals.debuggere")
set(ELEMENTS_APP_VERSION "1.0")

set(ELEMENTS_APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB DEBUGERE_VIEW_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.cpp)
file(GLOB DEBUGERE_VIEW_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.h)
list(APPEND ELEMENTS_APP_SOURCES ${DEBUGERE_VIEW_SOURCES})
list(APPEND ELEMENTS_APP_SOURCES ${DEBUGERE_VIEW_HEADERS})

#set(ELEMENTS_APP_RESOURCES
#   ${CMAKE_CURRENT_SOURCE_DIR}/res/WenQuanYiMicroHei.ttf
#)

include(AppIcon)
include(ElementsConfigApp)

# 这个库没有考虑通过 target properties 的方式使用，这里复制他的cmake可能之后改动就不兼容。
file(COPY ${CAIRO_DLL} DESTINATION "${ALL_OUT_DIR}")
file(COPY ${FREETYPE_DLL} DESTINATION "${ALL_OUT_DIR}")
file(COPY ${FONTCONFIG_DLL} DESTINATION "${ALL_OUT_DIR}")
file(COPY ${ICONV_DLL} DESTINATION "${ALL_OUT_DIR}")
file(COPY ${XML2} DESTINATION "${ALL_OUT_DIR}")

# 静态运行库 MT
if (DEBUGERE_VS_LINK_STATIC_MT)
    set_target_properties(
        debugere
        PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
    message(STATUS "msvc MT , element md")
endif()