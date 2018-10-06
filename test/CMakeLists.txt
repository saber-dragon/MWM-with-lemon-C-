file(GLOB SRCs "*.cpp")

foreach(src ${SRCs})
    get_filename_component(src_we ${src} NAME_WE)
    set(target_name ${src_we})
    add_executable(${target_name} ${src})
    target_link_libraries(${target_name} ${saber_libraries})
endforeach()