add_library(libconnectn
    connect_n.h connect_n.cpp
    coordinate.h
)

# {{{ test
add_executable(test_connect_n
	test_main.cpp
	lib_test.cpp
)
target_link_libraries(test_connect_n fmt::fmt-header-only Catch2::Catch2 libconnectn)

include(CTest)
enable_testing()
add_test(NAME test_connect_n COMMAND ./test_connect_n)
# }}}
