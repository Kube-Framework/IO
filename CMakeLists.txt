kube_add_library(IO
    SOURCES
        Base.hpp
        File.cpp
        File.hpp
        GetExecutablePath.hpp
        GetExecutablePath.ipp
        ResourceManager.cpp
        ResourceManager.hpp

    LIBRARIES
        Core
        whereami

    INCLUDES
        ${CMRC_INCLUDE_DIR}
)