set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

set(INCROOT ${PROJECT_SOURCE_DIR}/include/TEMM)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${INCROOT}/Application.hpp
    ${SRCROOT}/Application.cpp
    ${INCROOT}/Category.hpp
	${INCROOT}/Command.hpp
	${SRCROOT}/Command.cpp
	${INCROOT}/CommandQueue.hpp
	${SRCROOT}/CommandQueue.cpp
	${INCROOT}/DataTables.hpp
	${SRCROOT}/DataTables.cpp
    ${INCROOT}/GameState.hpp
    ${SRCROOT}/GameState.cpp
	${INCROOT}/KeyBinding.hpp
	${SRCROOT}/KeyBinding.cpp
	${INCROOT}/LuaState.hpp
	${INCROOT}/LuaState.inl
	${INCROOT}/Mob.hpp
	${SRCROOT}/Mob.cpp
	${INCROOT}/NodeFactory.hpp
	${SRCROOT}/NodeFactory.cpp
	${INCROOT}/Overworld.hpp
	${SRCROOT}/Overworld.cpp
	${INCROOT}/Player.hpp
	${SRCROOT}/Player.cpp
	${INCROOT}/ResourceHolder.hpp
	${INCROOT}/ResourceHolder.inl
	${INCROOT}/ResourceIdentifiers.hpp
	${INCROOT}/SceneNode.hpp
	${SRCROOT}/SceneNode.cpp
	${INCROOT}/SpriteNode.hpp
	${SRCROOT}/SpriteNode.cpp
    ${INCROOT}/State.hpp
    ${SRCROOT}/State.cpp
    ${INCROOT}/StateStack.hpp
    ${INCROOT}/StateStack.inl
    ${SRCROOT}/StateStack.cpp
	${INCROOT}/TileMap.hpp
	${SRCROOT}/TileMap.cpp
    ${INCROOT}/TitleState.hpp
    ${SRCROOT}/TitleState.cpp
	${INCROOT}/TMXParser.hpp
	${SRCROOT}/TMXParser.cpp
	${INCROOT}/Typedefs.hpp
	${INCROOT}/Utility.hpp
	${SRCROOT}/Utility.cpp
    ${SRCROOT}/Main.cpp
)

add_executable(purple_pikachu ${SRC})
target_link_libraries(purple_pikachu ${SFML_LIBRARIES})
target_link_libraries(purple_pikachu ${LUA_LIBRARIES})
