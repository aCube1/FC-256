include_guard()

function(set_debug_options target)
	target_compile_options(${target} PRIVATE -g -Og)

	# Enable CCACHE.
	find_program(CCACHE_PROGRAM ccache)
	if(CCACHE_PROGRAM)
		message(STATUS "CCache found!")

		set_target_properties(
			${target}
			PROPERTIES
				CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
				CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
		)
	endif()

	# Use address sanitizer flags.
	if (USE_SANITIZER_ASAN)
		message(STATUS "Using Address Sanitizer.")

		target_compile_options(
			${target}
			PRIVATE
				-fsanitize=address
				-fsanitize=leak
				-fsanitize=undefined
				-fno-omit-frame-pointer
		)

		target_link_options(
			${target}
			PRIVATE
				-fsanitize=address
				-fsanitize=leak
				-fsanitize=undefined
				-fno-omit-frame-pointer
		)
	endif()
endfunction()
