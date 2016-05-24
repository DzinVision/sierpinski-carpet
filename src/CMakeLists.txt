set(SOURCE_FILES
        main.cpp
        game.cpp
)

add_executable(Sierpinski_Carpet ${SOURCE_FILES})
target_link_libraries(Sierpinski_Carpet
        sfml-graphics
        sfml-window
        sfml-system
)
