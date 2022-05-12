kube_add_library(IO
    SOURCES
        Base.hpp
        File.cpp
        File.hpp
        ResourceManager.cpp
        ResourceManager.hpp

    LIBRARIES
        Core

    INCLUDES
        ${CMRC_INCLUDE_DIR}
)