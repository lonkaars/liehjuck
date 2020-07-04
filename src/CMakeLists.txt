add_executable(pws-engine 
    main.cpp
)

target_include_directories(pws-engine
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)
target_link_libraries(pws-engine 
    ${X11_LIBRARIES}
)

