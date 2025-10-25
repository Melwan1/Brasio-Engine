add_subdirectory(application)
add_subdirectory(events)

target_sources(testsuite PRIVATE
    dummy.cc
)
