file(GLOB sources CONFIGURE_DEPENDS *.hh *.cc)

set(target "${PROJECT_NAME}-util")
add_library(${target} INTERFACE) 
#target_include_directories(${target} INTERFACE ${sources})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(${target} ${PROJECT_DEPS} argparse::argparse botan::botan)
#target_include_directories(${target} PRIVATE ${PROJECT_BINARY_DIR})
#target_precompile_headers(${target} PUBLIC ${PROJECT_PCH})
