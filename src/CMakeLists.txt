set(SOURCES
	main.cpp

	cbs/Object.cpp
	cbs/ObjectManager.cpp
	cbs/components/Transform.cpp
	cbs/components/Camera.cpp
	cbs/components/Component.cpp
	cbs/components/PointLight.cpp
	cbs/components/DirectionalLight.cpp
	cbs/components/ThirdPersonController.cpp
	cbs/components/TextRenderer.cpp
	cbs/components/MeshRenderer/Mesh.cpp
	cbs/components/MeshRenderer/MeshRenderer.cpp
	cbs/components/RubiksCube/Cubie.cpp
	cbs/components/RubiksCube/RubiksCube.cpp

	cbs/message_system/MessageManager.cpp

	rendering/Cubemap.cpp
	rendering/DrawManager.cpp
	rendering/Drawable.cpp
	rendering/Line.cpp
	rendering/ShaderProgram.cpp

	scenes/Scene.cpp
	scenes/MainScene.cpp

	utilities/Input.cpp
	utilities/Time.cpp
	utilities/Window.cpp
	
	dependencies/glad.c
	dependencies/imgui/imconfig.h
	dependencies/imgui/imgui_impl_opengl3_loader.h
	dependencies/imgui/imgui_impl_opengl3.h
	dependencies/imgui/imgui_impl_opengl3.cpp
	dependencies/imgui/imgui_impl_glfw.h
	dependencies/imgui/imgui_impl_glfw.cpp
)

set(HEADERS
	cbs/Object.h
	cbs/ObjectManager.h
	cbs/components/Transform.h
	cbs/components/Camera.h
	cbs/components/Component.h
	cbs/components/PointLight.h
	cbs/components/DirectionalLight.h
	cbs/components/ThirdPersonController.h
	cbs/components/TextRenderer.h
	cbs/components/MeshRenderer/Mesh.h
	cbs/components/MeshRenderer/MeshRenderer.h
	cbs/components/RubiksCube/Cubie.h
	cbs/components/RubiksCube/RubiksCube.h
	cbs/components/RubiksCube/Tasks.h
	
	cbs/message_system/ConnectionInterfaces.h
	cbs/message_system/MessageIn.h
	cbs/message_system/MessageManager.h
	cbs/message_system/MessageOut.h
	cbs/message_system/PropertyIn.h
	cbs/message_system/PropertyOut.h
	cbs/message_system/TriggerIn.h
	cbs/message_system/TriggerOut.h

	rendering/Cubemap.h
	rendering/DrawManager.h
	rendering/Drawable.h
	rendering/ILightSource.h
	rendering/IWidget.h
	rendering/Line.h
	rendering/ShaderProgram.h

	scenes/Scene.h
	scenes/MainScene.h

	utilities/Input.h
	utilities/Time.h
	utilities/Window.h
)

add_executable(RubiksCube ${SOURCES} ${HEADERS})
target_link_libraries(RubiksCube ${CONAN_LIBS})
target_include_directories(RubiksCube PUBLIC ${PROJECT_SOURCE_DIR}/src)