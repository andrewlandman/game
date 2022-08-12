project(Cockpit)

add_executable(main
    main.cpp
    Camera.cpp
    EventReceiver.cpp
)

target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(main PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/libIrrlicht.a
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}.app/Contents/MacOS
)

add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/genplist.sh ${PROJECT_NAME}
          > ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}.app/Contents/Info.plist
)
