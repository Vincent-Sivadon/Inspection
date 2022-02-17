cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(Inspection)

# Liste des fichiers sources
file(GLOB SRCS "src/*.c")
# Liste des définitions
file(GLOB HEADERS "include/*.h")

add_library(Inspection SHARED ${SRCS} ${HEADERS})
target_link_libraries(Inspection)
target_include_directories(Inspection PRIVATE ${CMAKE_SOURCE_DIR}/include)

install(
  TARGETS Inspection
  EXPORT InspectionConfig
  ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib
  LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
  RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/Inspection)
export(TARGETS Inspection FILE "${CMAKE_SOURCE_DIR}/InspectionConfig.cmake")
install(EXPORT InspectionConfig DESTINATION "${CMAKE_SOURCE_DIR}/lib/cmake")

# Génère les tests  : la commande "ctest" permet de lancer tout les tests
enable_testing()
add_subdirectory(test)
