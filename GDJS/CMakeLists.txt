cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

project(GDJS)
#Dependencies on external libraries:
###
include_directories(${sfml_include_dir})
include_directories(${GDCORE_include_dir})
IF(WIN32) #Special case for wxWidgets on Windows
	include_directories(${wxwidgets_include_dir})
ELSEIF (NOT EMSCRIPTEN AND NOT NO_GUI)
	find_package(wxWidgets COMPONENTS core base adv net ribbon stc aui propgrid richtext html xrc REQUIRED)
	include( "${wxWidgets_USE_FILE}" )
	include_directories(${GTK_INCLUDE_DIRS})
	link_directories(${GTK_LIBRARY_DIRS})
ENDIF(WIN32)

#Defines
###
add_definitions( -DGD_IDE_ONLY )
IF (EMSCRIPTEN) #When compiling for the web, we do not want any GUI related feature.
	add_definitions( -DGD_NO_WX_GUI )
	add_definitions( -DEMSCRIPTEN )
ENDIF()
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	add_definitions( -DDEBUG )
	IF(WIN32)
		add_definitions( __WXDEBUG__ )
	ENDIF(WIN32)
ELSEIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	add_definitions( -DRELEASE )
ELSE()
	add_definitions( -DDEV )
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

IF(WIN32)
	add_definitions( -DWINDOWS )
	add_definitions( "-DGD_API=__declspec(dllexport)" )
	add_definitions( "-DGD_CORE_API=__declspec( dllimport )" )

	add_definitions( -D__GNUWIN32__ )
	add_definitions( -D__WXMSW__ )
	add_definitions( -DwxUSE_UNICODE=1 )
	add_definitions( -DWXUSINGDLL )
ELSE()
    IF(APPLE)
    add_definitions( -DMACOS )
    ELSE()
	add_definitions( -DLINUX )
	ENDIF()
	add_definitions( -DGD_API= )
	add_definitions( -DGD_CORE_API= )
	add_definitions(${GTK_CFLAGS_OTHER})
ENDIF(WIN32)

#The target
###
include_directories(.)
file(GLOB f1 GDJS/*)
file(GLOB_RECURSE f2 GDJS/Bindings/* GDJS/BuiltinExtensions/* GDJS/mongoose/*)
set(source_files ${f1} ${f2})
IF(NOT EMSCRIPTEN)
file(GLOB_RECURSE f3 GDJS/Dialogs/*)
set(source_files ${source_files} ${f3})
ENDIF()

add_library(
        GDJS
        SHARED
        ${source_files}
)
IF(EMSCRIPTEN)
	set_target_properties(GDJS PROPERTIES SUFFIX ".bc")
ELSEIF(WIN32)
	set_target_properties(GDJS PROPERTIES PREFIX "")
ELSE()
	set_target_properties(GDJS PROPERTIES PREFIX "lib")
ENDIF()
set_target_properties(GDJS PROPERTIES MACOS_RPATH "..")
set(LIBRARY_OUTPUT_PATH ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/JsPlatform)
set(ARCHIVE_OUTPUT_PATH ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/JsPlatform)
set(RUNTIME_OUTPUT_PATH ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/JsPlatform)

#Linker files
###
IF(EMSCRIPTEN)
	#Nothing.
ELSE()
	target_link_libraries(GDJS GDCore)
	target_link_libraries(GDJS ${sfml_LIBRARIES})
	target_link_libraries(GDJS ${wxWidgets_LIBRARIES}) #Add wxWidgets libraries if needed.
	target_link_libraries(GDJS ${GTK_LIBRARIES}) #Add GTK libraries if needed (Linux only).
ENDIF()

#Post build tasks
###
IF(EMSCRIPTEN)
	#Nothing.
ELSE()
	IF(WIN32)
		add_custom_command(TARGET GDJS
			POST_BUILD
			COMMAND "${GD_base_dir}/GDJS/scripts/CopyRuntimeToGD.bat")
	ELSE()
		add_custom_command(TARGET GDJS
			POST_BUILD
			COMMAND sh "CopyRuntimeToGD.sh" ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/JsPlatform/Runtime
			WORKING_DIRECTORY ${GD_base_dir}/GDJS/scripts)
	ENDIF()
ENDIF()
