set(DEFAULT_PROJECT_VERSION_PRIME 5)
set(DEFAULT_PROJECT_VERSION_MAJOR 2)
set(DEFAULT_PROJECT_VERSION_MINOR 11)
set(DEFAULT_PROJECT_VERSION_MICRO 0)

if(DEFINED PROJECT_VERSION_PRIME)
  if(NOT ${DEFAULT_PROJECT_VERSION_PRIME} STREQUAL ${PROJECT_VERSION_PRIME})
    message(FATAL_ERROR "Variable DEFAULT_PROJECT_VERSION_PRIME=" ${DEFAULT_PROJECT_VERSION_PRIME} " in VERSION.cmake differs from PROJECT_VERSION_PRIME=" ${PROJECT_VERSION_PRIME} " in spec")
  endif()
else()
  set (VERSION_PRIME ${DEFAULT_PROJECT_VERSION_PRIME})
endif()

if(DEFINED PROJECT_VERSION_MAJOR)
  if(NOT ${DEFAULT_PROJECT_VERSION_MAJOR} STREQUAL ${PROJECT_VERSION_MAJOR})
    message(FATAL_ERROR "Variable DEFAULT_PROJECT_VERSION_MAJOR=" ${DEFAULT_PROJECT_VERSION_MAJOR} " in VERSION.cmake differs from PROJECT_VERSION_MAJOR=" ${PROJECT_VERSION_MAJOR} " in spec")
  endif()
else()
  set (VERSION_MAJOR ${DEFAULT_PROJECT_VERSION_MAJOR})
endif()

if(DEFINED PROJECT_VERSION_MINOR)
  if(NOT ${DEFAULT_PROJECT_VERSION_MINOR} STREQUAL ${PROJECT_VERSION_MINOR})
    message(FATAL_ERROR "Variable DEFAULT_PROJECT_VERSION_MINOR=" ${DEFAULT_PROJECT_VERSION_MINOR} " in VERSION.cmake differs from PROJECT_VERSION_MINOR=" ${PROJECT_VERSION_MINOR} " in spec")
  endif()
else()
  set (VERSION_MINOR ${DEFAULT_PROJECT_VERSION_MINOR})
endif()

if(DEFINED PROJECT_VERSION_MICRO)
  if(NOT ${DEFAULT_PROJECT_VERSION_MICRO} STREQUAL ${PROJECT_VERSION_MICRO})
    message(FATAL_ERROR "Variable DEFAULT_PROJECT_VERSION_MICRO=" ${DEFAULT_PROJECT_VERSION_MICRO} " in VERSION.cmake differs from PROJECT_VERSION_MICRO=" ${PROJECT_VERSION_MICRO} " in spec")
  endif()
else()
  set (VERSION_MICRO ${DEFAULT_PROJECT_VERSION_MICRO})
endif()
