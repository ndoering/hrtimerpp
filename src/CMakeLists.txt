add_library (hrtimerpp SHARED
    Timestamp.cpp
    Timer.cpp
    Timerseries.cpp
    Statistic.cpp)

target_link_libraries (hrtimerpp m)

set_target_properties (hrtimerpp
    PROPERTIES VERSION ${VERSION_COMPLETE} SOVERSION ${VERSION_MAJOR}
)

install (TARGETS hrtimerpp DESTINATION lib)
install (FILES hrtimerpp.h DESTINATION include)
install (FILES Timestamp.h DESTINATION include/hrtimerpp)
install (FILES Timer.h DESTINATION include/hrtimerpp)
install (FILES Timerseries.h DESTINATION include/hrtimerpp)
install (FILES Statistic.h DESTINATION include/hrtimerpp)
