cmake_minimum_required(VERSION 3.15.0)
set(CMAKE_TOOLCHAIN_FILE "/home/amilani/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
project(main VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

#From "Working with CMake" documentation:
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # AddressSanitizer (ASan)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # UndefinedBehaviorSanitizer (UBSan)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

#Copy resources folder to build folder
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

#Configurar explícitamente la ubicación de raylib si es necesario
set(raylib_DIR "/home/francob/dev/vcpkg/installed/x64-linux/share/raylib")
find_package(raylib CONFIG REQUIRED)

#Agregar GLFW
find_package(glfw3 CONFIG REQUIRED)

add_executable(main main.cpp CSVData.cpp Text.cpp Lequel.cpp)

target_include_directories(main PRIVATE ${raylib_INCLUDE_DIRS})
#Agregar glfw a las bibliotecas vinculadas
target_link_libraries(main PRIVATE ${raylib_LIBRARIES} glfw)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # From "Working with CMake" documentation:
    target_link_libraries(main PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(main PRIVATE m ${CMAKE_DL_LIBS} pthread GL rt X11)
endif()