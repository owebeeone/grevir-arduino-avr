cmake_minimum_required(VERSION 3.20)
project(grevir_arduino_avr VERSION 0.1.0 LANGUAGES CXX)

if(NOT TARGET grevir::arduino)
  find_package(grevir-arduino CONFIG REQUIRED)
endif()

foreach(dependency IN ITEMS avr core peripherals)
  if(NOT TARGET grevir::${dependency})
    find_package(grevir-${dependency} CONFIG REQUIRED)
  endif()
endforeach()

add_library(grevir_arduino_avr INTERFACE)
add_library(grevir::arduino_avr ALIAS grevir_arduino_avr)
set_target_properties(grevir_arduino_avr PROPERTIES EXPORT_NAME arduino_avr)
target_compile_features(grevir_arduino_avr INTERFACE cxx_std_23)
target_link_libraries(grevir_arduino_avr INTERFACE
  grevir::arduino grevir::avr grevir::core grevir::peripherals)
target_include_directories(grevir_arduino_avr INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

include(GNUInstallDirs)
install(TARGETS grevir_arduino_avr EXPORT GrevirArduinoAVRTargets)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING
  PATTERN "*.hpp" PATTERN "*.h")
install(EXPORT GrevirArduinoAVRTargets NAMESPACE grevir::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-arduino-avr)
install(FILES cmake/grevir-arduino-avr-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-arduino-avr)
install(FILES LICENSE.txt DESTINATION ${CMAKE_INSTALL_DATADIR}/grevir-arduino-avr)

option(GREVIR_BUILD_COMPILE_CHECKS "Compile native headers and template users" OFF)
option(GREVIR_BUILD_HOST_TESTS "Run deterministic native behavior tests" OFF)
if(GREVIR_BUILD_HOST_TESTS)
  enable_testing()
endif()
if(GREVIR_BUILD_COMPILE_CHECKS OR GREVIR_BUILD_HOST_TESTS)
  add_subdirectory(tests)
endif()
