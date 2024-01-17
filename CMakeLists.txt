cmake_minimum_required(VERSION 3.5)

project(ExchangeStationRecog)

set(CMKAE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/hikvision/64/)

add_executable(main     ExchangeStationRecog/src/test.cpp 
                        ExchangeStationRecog/src/ExStationRecog.cpp 
                        GxCamera/GxCamera.cpp)

set(OpenCV_INCLUDE_DIRS "/usr/local/include/opencv4")
set(OpenCV_LIBS opencv_core opencv_highgui opencv_calib3d  opencv_imgproc)
set(HIKVISION_CAMERA_DIR "${PROJECT_SOURCE_DIR}/hikvision")
set(ADDITIONAL_LIBS -lgxiapi)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)

include_directories(GxCamera)
include_directories(GxCamera/GxSDK)
include_directories(${HIKVISION_CAMERA_DIR}/include)
include_directories(${HIKVISION_CAMERA_DIR}/tool/include)
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(main PRIVATE ${EIGEN3_INCLUDE_DIRS})
target_link_libraries(main PRIVATE      ${OpenCV_LIBS}
                                        pthread
                                        yaml-cpp
                                        gxiapi)


#target_link_libraries(main PRIVATE FormatConversion)
#target_link_libraries(main PRIVATE GCBase_gcc421_v3_0)
#target_link_libraries(main PRIVATE GenApi_gcc421_v3_0)
#target_link_libraries(main PRIVATE Log_gcc421_v3_0)
#target_link_libraries(main PRIVATE log4cpp_gcc421_v3_0)
#target_link_libraries(main PRIVATE MathParser_gcc421_v3_0)
#target_link_libraries(main PRIVATE MediaProcess)
#target_link_libraries(main PRIVATE MvCameraControl)
#target_link_libraries(main PRIVATE MvUsb3vTL)
#target_link_libraries(main PRIVATE MVGigEVisionSDK)
#target_link_libraries(main PRIVATE MVRender)
#target_link_libraries(main PRIVATE NodeMapData_gcc421_v3_0)
#target_link_libraries(main PRIVATE XmlParser_gcc421_v3_0)



#file(GLOB LIBS_PATH "hikvision/64/*.so")
#foreach(LIB_PATH ${LIBS_PATH})
        #get_filename_component(LIB_NAME ${LIB_PATH}  NAME_WE)
        #target_link_libraries(main PRIVATE ${LIB_NAME} )
#endforeach()