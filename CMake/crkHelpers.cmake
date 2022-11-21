# Usage:
#    crk_setup_target(
#       TARGET                  <target>
#       CRK_INCLUDE_DIR         <path_to_crk_library_include_dir>
#       WORK_DIR                <working_directory>
#       CRK_SETTINGS_DIR_PATH   <path_to_crk_settings_directory>
#       CRK_SETTINGS_FILENAME   <crk_settings_filename>
#    )
#
# Arguments:
#   TARGET
#       Name of the target to setup.
#
#   CRK_INCLUDE_DIR:
#       Path to the crk library Include/ directory.
#
#   WORK_DIR:
#       Working directory used to run the generator.
#       All path settings contained in the crk settings file can be defined relatively to WORK_DIR.
#       If unspecified, defaults to ${PROJECT_SOURCE_DIR}.
#
#   CRK_SETTINGS_DIR_PATH:
#       Path to directory containing the crk settings file.
#       If unspecified, defaults to "${WORK_DIR}".
#
#   CRK_SETTINGS_FILENAME:
#       Name of the crk settings file, including the extension.
#       If unspecified, defaults to "crkSettings.toml".
function(crk_setup_target)

    cmake_parse_arguments(
        FUNC_ARGS
        ""
        "TARGET;WORK_DIR;CRK_SETTINGS_DIR_PATH;CRK_SETTINGS_FILENAME"
        ""
        ${ARGN}
    )

    #### Check / Setup function parameters

    if (NOT FUNC_ARGS_TARGET)
        message(FATAL_ERROR "Missing TARGET argument")
    endif()

    if (NOT FUNC_ARGS_CRK_INCLUDE_DIR)
        message(FATAL_ERROR "Missing CRK_INCLUDE_DIR argument")
    endif()

    if (NOT FUNC_ARGS_WORK_DIR)
        set(FUNC_ARGS_WORK_DIR ${PROJECT_SOURCE_DIR})
    endif()

    if (NOT FUNC_ARGS_CRK_SETTINGS_DIR_PATH)
        set(FUNC_ARGS_CRK_SETTINGS_DIR_PATH "${FUNC_ARGS_WORK_DIR}")
    endif()

    if (NOT FUNC_ARGS_CRK_SETTINGS_FILENAME)
        set(FUNC_ARGS_CRK_SETTINGS_FILENAME "crkSettings.toml")
    endif()

    #### Supply crk include directory to TARGET
    
    target_link_libraries(${FUNC_ARGS_TARGET} PUBLIC Refureku)

    #### Setup generator

    add_custom_target(RunCrkGenerator
                        WORKING_DIRECTORY ${FUNC_ARGS_WORK_DIR}
                        COMMAND crkGenerator "${FUNC_ARGS_CRK_SETTINGS_DIR_PATH}/${FUNC_ARGS_CRK_SETTINGS_FILENAME}") 

    add_dependencies(${FUNC_ARGS_TARGET} RunCrkGenerator)

endfunction()