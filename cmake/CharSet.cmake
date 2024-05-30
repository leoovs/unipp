set(CHARSET_UTF8 "UTF-8")

function(translate_charset_flag OUTPUT_FLAG CHARSET)
	if(${CHARSET} STREQUAL ${CHARSET_UTF8})
		if(MSVC)
			set(${OUTPUT_FLAG} "/source-charset:utf-8" PARENT_SCOPE)
		else()
			set(${OUTPUT_FLAG} "-finput-chatset=utf-8" PARENT_SCOPE)
		endif()
	else()
		message(SEND_ERROR "Specified character set '${CHARSET}' is not currently supported")
	endif()
endfunction()

function(set_source_charset TARGET CHARSET)
	translate_charset_flag(CHARSET_FLAG ${CHARSET})

	target_compile_options(
		${TARGET}
		PRIVATE # Let's be careful and set this on a per-project basis.
		${CHARSET_FLAG}
	)
endfunction()

function(enforce_msvc_utf8 TARGET)
	if(MSVC)
		set_source_charset(${TARGET} ${CHARSET_UTF8})
	endif()
endfunction()

