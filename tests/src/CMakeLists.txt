add_subdirectory(events)
add_subdirectory(math)

target_sources(testsuite PRIVATE
    dummy.cc
)
