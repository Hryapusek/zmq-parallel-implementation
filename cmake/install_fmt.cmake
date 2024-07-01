function(install_fmt)    
    message(STATUS "Loading fmt library...")    
    include(FetchContent)
        FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt
            GIT_TAG e69e5f9
        )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(fmt)
    message(STATUS "Loading fmt library finished")    
endfunction(install_fmt)
