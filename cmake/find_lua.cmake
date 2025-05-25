
FIND_LIBRARY(LIB_LUA 
	NAMES lua lua54
)


IF (NOT LIB_LUA)
	#IF (WIN32)
	#	FILE(DOWNLOAD "https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/lua-5.4.2_Win64_dll17_lib.zip/download" "c:/tmp")
	#ENDIF()

	FIND_LIBRARY(LIB_LUA 
		NAMES lua lua54
	)
ENDIF ()

TARGET_LINK_LIBRARIES(${APP_NAME} INTERFACE ${LIB_LUA})