
IF(USE_FORTRAN)
	SET(F95_SOURCES
		"src/engine/maths/core.f95"
	)
ENDIF()

SET(ASM_SOURCE
)

SET(C_SOURCES
	"src/engine-posix/string.c"
	"src/engine-posix/time.c"
	"src/engine-posix/unistd.c"
	"src/engine-sys/file.c"
	"src/engine-sys/filesystem.c"
	"src/engine-sys/info.c"
	"src/engine-sys/library.c"
	"src/engine-sys/memory.c"
	"src/engine-sys/memory/arena.c"
	"src/engine-sys/memory/core.c"
	"src/engine-sys/memory/freelist.c"
	"src/engine-sys/memreq.c"

	"src/engine-sys/socket.c"

	"src/engine-testing/exceptions.c"
	"src/engine-testing/unite.c"

	"src/engine/arg_parser.c"
	"src/engine/config.c"
	"src/engine/convert.c"
	"src/engine/data/hashmap_lazy.c"
	"src/engine/debug/benchmark.c"
	"src/engine/debug/error.c"
	"src/engine/debug/logger.c"
	"src/engine/debug/signalar.c"
	"src/engine/game/actions.c"
	"src/engine/game/entity.c"
	"src/engine/game/loader.c"
	"src/engine/images/loader.c"
	"src/engine/loader/asset.c"
	"src/engine/lua/api.c"
	"src/engine/lua/api/file.c"
	"src/engine/lua/api/filesystem.c"
	"src/engine/lua/api/maths.c"
	"src/engine/lua/config.c"
	"src/engine/lua/helpers.c"
	"src/engine/maths/core.c"
	"src/engine/maths/memory.c"
	"src/engine/print.c"
	"src/engine/render.c"
	"src/engine/string.c"
	"src/engine/window.c"
	"src/engine/wolfhound.c"
)

SET(VULKAN_SOURCES
	"src/engine-backends/vulkan/vulkan.c"
)

SET(RAYLIB_SOURCES
	"src/engine-backends/raylib/debug.c"
	"src/engine-backends/raylib/render.c"
	"src/engine-backends/raylib/window.c"
)

SET(SDL3_SOURCES
	"src/engine-backends/sdl3/render.c"
	"src/engine-backends/sdl3/window.c"
)

IF(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
	LIST(APPEND ASM_SOURCE
		"src/engine-asm/x64_sv_stdatomic.asm"
	)
ENDIF()

IF (NOT NO_CXX_COMPILER)
	SET(CXX_SOURCES
		"src/engine-cpp/wolfhound.cpp"
		"src/engine-cpp/print.cpp"
		"src/engine-cpp/memory.cpp"
		"src/engine-cpp/maths/core.cpp"
	)
ENDIF()
