# Créer un executable à partir de fichiers sources
add_executable(testvecteur  testvecteur.cxx)
add_executable(testParticle  testParticle.cxx)
add_executable(testUnivers  testUnivers.cxx)
add_executable(testStromer  testStromer.cxx)
add_executable(edo edo.cxx)
add_executable(trace trace.cxx)


# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(testvecteur particules)
target_link_libraries(testParticle particules)
target_link_libraries(testUnivers particules)
target_link_libraries(testStromer particules)


## Mise en place de Gtest
enable_testing()

add_executable(googletest gtest.cc)

target_link_libraries(googletest particules gtest_main)

include(GoogleTest)
gtest_discover_tests(googletest)
