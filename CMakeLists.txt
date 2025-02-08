cmake_minimum_required(VERSION 3.22)

# Project name
project(mt_scratches)
set(LIB_NAME ${PROJECT_NAME}_lib)

# Remove unnecessary generated configs
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
option(BUILD_TESTING "Enables testing" ON)


add_compile_definitions(
    # Use Unicode defines
	_UNICODE
	UNICODE

    # Disable MSVC CRT warnings
	_CRT_SECURE_NO_DEPRECATE
	_CRT_NONSTDC_NO_DEPRECATE

    # Remove old stuff from windows.h
	WIN32_LEAN_AND_MEAN
	NOMINMAX

    # Add debug and release defines
	$<$<CONFIG:Debug>:_DEBUG>
	$<$<CONFIG:Release>:NDEBUG>
)

# Hide all exported symbols by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Hide all exported inline symbols by default
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# Enable C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# add libs
# ex: find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

if (MSVC)
	# Global compiler options
	# Note that by default, Debug build will have:
	#  /Od   [optimization disabled] 
	#  /RTC1 [runtime checks for uninit variables and stack usage]
	#  /MDd  [use debug runtime]
	# Release build will have:
	#  /O2   [optimization for max speed]
	#  /Ob2  [full inline expansion]
	#  /MD   [use release runtime]

	add_compile_options(
		/W3				# Warning Level 4
		/WX				# Treat warnings as errors
		/Gy				# Enable function level linking
		/Gw				# Optimize Global Data
		/GR-			# Disable RTTI
		/bigobj			# Increase number of sections in obj files
		/Oi				# Enable intrinsics
		/fp:fast		# Enable fast math
		/permissive-	# Enable standards conformance mode to the compiler
		$<$<CONFIG:Release>:/GL> # Enable Global Optimizations
	)

	# Global linker options
	add_link_options(
		/WX	# Treat warnings as errors
		$<$<CONFIG:Debug>:/DEBUG:FASTLINK>	# Fast Link for debug build
		$<$<CONFIG:Release>:/LTCG>			# Enable Link-Time Code Generation (used by GL)
	)
endif()

set(PROJECT_SOURCES
	src/singletones.cpp
)

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC include)

if (BUILD_TESTING)
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif ()
