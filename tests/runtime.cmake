if(NOT COMMAND catch_discover_tests)
  find_package(grevir-test-support CONFIG REQUIRED)
endif()
add_executable(grevir_arduino_avr_runtime arduino_avr_test.cpp)
target_link_libraries(grevir_arduino_avr_runtime PRIVATE grevir::arduino_avr Catch2::Catch2WithMain)
target_compile_definitions(grevir_arduino_avr_runtime PRIVATE GREVIR_ARDUINO_HOST_MOCK)
set_target_properties(grevir_arduino_avr_runtime PROPERTIES CXX_EXTENSIONS OFF)
catch_discover_tests(grevir_arduino_avr_runtime TEST_PREFIX "arduino_avr."
  PROPERTIES LABELS "arduino_avr" TIMEOUT 10)
