add_executable(HelloWorld "HelloWorld.cpp")
add_executable(HelloWorld_Numeric_Derivative "HelloWorld_Numeric_Derivative.cpp")
add_executable(HelloWorld_Analytic_Derivative "HelloWorld_Analytic_Derivative.cpp")
add_executable(PowellFunctionTutorial "PowellFunctionTutorial.cpp")

find_package(Ceres REQUIRED)

include_directories(HelloWorld ${CERES_INCLUDE_DIRS})
include_directories(HelloWorld_Numeric_Derivative ${CERES_INCLUDE_DIRS})
include_directories(HelloWorld_Analytic_Derivative ${CERES_INCLUDE_DIRS})
include_directories(PowellFunctionTutorial ${CERES_INCLUDE_DIRS})

target_link_libraries(HelloWorld ${CERES_LIBRARIES})
target_link_libraries(HelloWorld_Numeric_Derivative ${CERES_LIBRARIES})
target_link_libraries(HelloWorld_Analytic_Derivative ${CERES_LIBRARIES})
target_link_libraries(PowellFunctionTutorial ${CERES_LIBRARIES})
