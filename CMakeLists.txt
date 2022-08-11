cmake_minimum_required(VERSION 3.2)

project(game)

add_executable(main
    main.cpp
    Camera.cpp
    EventReceiver.cpp
)

target_include_directories(main PUBLIC
    include/
)

target_link_libraries(main PUBLIC
    /Users/andrew/Desktop/game/lib/libIrrlicht.a
    #lib/libIrrlicht.a    
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ../bin/Game.app/Contents/MacOS
)
