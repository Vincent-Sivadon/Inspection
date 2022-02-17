# GENERATION DES TESTS POUR VERSION AVEC MATRICE D'ADJACENCE ==============

find_package(Inspection REQUIRED PATHS ${CMAKE_SOURCE_DIR}/lib)

file(GLOB TEST_SRCS "*.c")

# pour chaque TEST
foreach(testsourcefile ${TEST_SRCS})
  # file ( GLOB ... ) donne les path absolu, on le transform en relative path
  # exemple :
  # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/tests/src/areConnectedTests"
  # transformé en : "areConnectedTests"
  string(REPLACE ".c" "" testname ${testsourcefile})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" testname ${testname})

  # on créé l'executable
  add_executable(${testname} ${testsourcefile})

  # Library linking
  target_include_directories(${testname} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(${testname} PUBLIC Inspection)
  target_compile_options(${testname} PUBLIC -O3)

  # on ajoute cet executable à la liste des tests
  add_test(${testname} ${testname})

endforeach(testsourcefile ${TEST_SRCS})
