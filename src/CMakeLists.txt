add_library (hrtimerpp SHARED Timestamp.cpp)

target_link_libraries (hrtimerpp m)

install (TARGETS hrtimerpp DESTINATION lib)
install (FILES Timestamp.h DESTINATION include)
