set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

set(INCROOT ${PROJECT_SOURCE_DIR}/include/TEMM)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${INCROOT}/Application.hpp
    ${SRCROOT}/Application.cpp
    ${INCROOT}/GameState.hpp
    ${SRCROOT}/GameState.cpp
    ${INCROOT}/State.hpp
    ${SRCROOT}/State.cpp
    ${INCROOT}/StateStack.hpp
    ${INCROOT}/StateStack.inl
    ${SRCROOT}/StateStack.cpp
    ${INCROOT}/TitleState.hpp
    ${SRCROOT}/TitleState.cpp
    ${SRCROOT}/Main.cpp
)

add_executable(purple_pikachu ${SRC})
target_link_libraries(purple_pikachu ${SFML_LIBRARIES})
