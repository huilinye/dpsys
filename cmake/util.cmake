
function(dpsys_add_executable targetname srcs depends libs)
    add_executable(${targetname} ${srcs})
    add_dependencies(${targetname} ${depends})
    target_link_libraries(${targetname} ${libs})
endfunction()