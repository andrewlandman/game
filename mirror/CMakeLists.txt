project(Mirror)

add_executable(mirror
    main.cpp
    Camera.cpp
    EventReceiver.cpp
    InputHandler.cpp
    Quaternion.cpp
    Scene.cpp
)

target_include_directories(mirror PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(mirror PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/libIrrlicht.a
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

set_target_properties(mirror PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}.app/Contents/MacOS
)

add_custom_command(
    TARGET mirror
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/genplist.sh ${PROJECT_NAME}
          > ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}.app/Contents/Info.plist
)
