cmake_minimum_required(VERSION 3.10)
project(MovingHelloWorld)

find_package(X11 REQUIRED)

add_executable(MovingHelloWorld)

target_sources(MovingHelloWorld
    PRIVATE
        hello_world.c 
        file_size_calculator.c  
)

target_link_libraries(MovingHelloWorld 
    PRIVATE 
        ${X11_LIBRARIES}
)

target_include_directories(MovingHelloWorld 
    PRIVATE 
        ${X11_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/fisier_intrare.txt 
    ${CMAKE_CURRENT_BINARY_DIR}/fisier_intrare.txt 
    COPYONLY
)
