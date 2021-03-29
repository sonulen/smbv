add_executable(smbv-unit-tests main.cpp)

target_link_libraries(
    smbv-unit-tests
    PRIVATE smbv
)

add_custom_target(check ALL COMMAND smbv-unit-tests)