if(MSVC OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND WIN32))
    # Generate PDB files for release builds
    add_link_options($<$<CONFIG:Release,MinSizeRel>:LINKER:/DEBUG:FULL>)
    # Disable incremental linking + optimize
    add_link_options(
        $<$<CONFIG:Release,MinSizeRel,RelWithDebInfo>:LINKER:/INCREMENTAL:NO>
        $<$<CONFIG:Release,MinSizeRel,RelWithDebInfo>:LINKER:/OPT:REF>
        $<$<CONFIG:Release,MinSizeRel,RelWithDebInfo>:LINKER:/OPT:ICF>
    )
    # Enable big objects
    if(MSVC)
        add_compile_options(/bigobj)
    else()
        add_compile_options(-Wa,-mbig-obj)
    endif()
endif()