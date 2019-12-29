add_executable(1_FromTutorial "1_FromTutorial.cpp")

find_package(Ceres REQUIRED)

target_link_libraries(1_FromTutorial ${CERES_LIBRARIES})
