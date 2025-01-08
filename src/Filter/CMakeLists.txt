cmake_minimum_required(VERSION 3.16)
project(Filter CXX)

set(HEADERS
    # Base
    include/KalmanFilterBase.hpp
    include/StandardBase.hpp
    include/SquareRootBase.hpp
    include/StandardFilterBase.hpp
    include/SquareRootFilterBase.hpp

    # EKF
    include/ExtendedKalmanFilter.hpp
    include/SquareRootExtendedKalmanFilter.hpp

    # UKF
    include/UnscentedKalmanFilterBase.hpp
    include/UnscentedKalmanFilter.hpp
    include/SquareRootUnscentedKalmanFilter.hpp

    # Models
    include/MeasurementModel.hpp
    include/SystemModel.hpp
    include/LinearizedMeasurementModel.hpp
    include/LinearizedSystemModel.hpp

    # Utils
    include/Matrix.hpp
    include/Types.hpp
)

find_package(Eigen3 REQUIRED)

include_directories(
    ./include
    ${Eigen3_INCLUDE_DIR}
)


add_library(Filter ${HEADERS})

set_target_properties(Filter PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Filter Eigen3::Eigen)

target_include_directories(Filter PUBLIC include)
