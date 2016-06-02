set(SOURCES
  ${PROJECT_SOURCE_DIR}/src/algorithm/IFXStrategy.cpp
  ${PROJECT_SOURCE_DIR}/src/algorithm/RateStrategy.cpp
  ${PROJECT_SOURCE_DIR}/src/repository/IFXRepository.cpp
  ${PROJECT_SOURCE_DIR}/src/client/FXATClient.cpp
)

add_library(
  ${PROJECT_NAME}
  OBJECT
  ${SOURCES}
)

add_executable(
  ${PROJECT_NAME}-bin
  $<TARGET_OBJECTS:${PROJECT_NAME}>
  ${PROJECT_SOURCE_DIR}/src/main.cpp
)

include_directories (${INCLUDE_ROOT_DIR})