file(GLOB sources CONFIGURE_DEPENDS *.hh *.cc)

set(target "${PROJECT_NAME}-termapp")
add_executable(${target} ${sources}) 
target_link_libraries(${target} ${PROJECT_DEPS} argparse::argparse botan::botan ${PROJECT_NAME}-util)
target_include_directories(${target} PRIVATE ${PROJECT_BINARY_DIR})
target_precompile_headers(${target} PUBLIC ${PROJECT_PCH})
