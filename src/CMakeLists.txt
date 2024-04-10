add_subdirectory(img)
add_subdirectory(math)
add_subdirectory(model)
add_subdirectory(util)

set(OAR_LIBS
        oar_img
        oar_math
        oar_model
        oar_util)

add_executable(Oar main.cpp)

target_link_libraries(Oar PUBLIC ${OAR_LIBS})
target_include_directories(Oar PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
