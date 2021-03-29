cmake_minimum_required(VERSION 3.1...3.19)

project(smbv VERSION "1.0" LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

# Establish the project options
option(SMBV_BUILD_EXAMPLES "Set to ON to build examples" ON)
option(SMBV_BUILD_TESTS "Set to ON to build tests" ON)

# Включение 17 стандарта.
set(CMAKE_CXX_STANDARD 17)

################################################################################
##
##      Опции компиляции
##
################################################################################

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

################################################################################
##
##      Заголовочная библиотека
##
################################################################################

add_library(smbv INTERFACE)

target_include_directories(smbv INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(smbv INTERFACE cxx_std_17)

add_library(mtl::smbv ALIAS smbv)

################################################################################
##
##      Пример использования
##
################################################################################

if (NOT SMBV_BUILD_EXAMPLES)
    message(STATUS "Сборка примеров использования smbv выключена")
elseif(IS_SUBPROJECT)
    message(STATUS "smbv примеры не собираются в режиме подмодуля")
else()
    add_subdirectory(src)
endif()

################################################################################
##
##      Тесты
##
################################################################################

if(NOT SMBV_BUILD_TESTS)
    message(STATUS "Тестирование проекта smbv выключено")
elseif(IS_SUBPROJECT)
    message(STATUS "smbv не тестируется в режиме подмодуля")
else()
    add_subdirectory(test)
endif()


