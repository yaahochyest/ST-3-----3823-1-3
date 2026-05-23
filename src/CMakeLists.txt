set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(header ${header_path}/TimedDoor.h)
set(src TimedDoor.cpp)

# === LIBRARY ===
add_library(${PROJECT_NAME} STATIC
  ${header}
  ${src}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${header_path}
)

# === MAIN EXECUTABLE ===
add_executable(${PROJECT_NAME}.info
  main.cpp
)

target_include_directories(${PROJECT_NAME}.info
  PUBLIC
    ${header_path}
)

target_link_libraries(${PROJECT_NAME}.info
  PRIVATE
    ${PROJECT_NAME}
)

# === INSTALL ===
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION "${lib_dest}"
        LIBRARY DESTINATION "${lib_dest}"

        COMPONENT library)

install(TARGETS ${PROJECT_NAME}.info
        RUNTIME DESTINATION "${tool_dest}"
        COMPONENT library)

install(FILES ${header}
        DESTINATION "${include_dest}")
