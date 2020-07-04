add_executable(pws-engine 
    main.cpp
)

target_link_libraries(pws-engine 
    ${X11_LIBRARIES}
)

