function(generate_packages NAME)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libpurple0 (>= ${PURPLE_VERSION})") # TODO: libglib2.0-0 could be added here, but it is non-trivial to do. libpurple0 depends on it anyway, so we should be good.
    if (${OPUSFILE_FOUND})
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libopusfile0 (>= ${OPUSFILE_VERSION})")
    endif()
    if ("${PIXBUF_FOUND}")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libgdk-pixbuf-2.0-0 (>= ${PIXBUF_VERSION})")
    endif()
    set(CPACK_GENERATOR "DEB")

    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_SOURCE_PACKAGE_VERSION ${PROJECT_VERSION})

    set(CPACK_PACKAGE_FILE_NAME ${NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME})

    include(CPack)
endfunction()
