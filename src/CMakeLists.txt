add_library (hrtimerpp SHARED
    Timestamp.cpp
    Timer.cpp)

target_link_libraries (hrtimerpp m)

install (TARGETS hrtimerpp DESTINATION lib)
install (FILES hrtimerpp.h DESTINATION include)
install (FILES Timestamp.h DESTINATION include/hrtimerpp)
install (FILES Timer.h DESTINATION include/hrtimerpp)
