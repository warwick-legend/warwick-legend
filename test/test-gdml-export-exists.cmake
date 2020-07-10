# Usage:
#  cmake -DGDML_FILE=/path/to/file.gdml -P test-gdml-export-exists.cmake
#
# Compare hash on input gdml file to an expected hash
# - At present only checks that file exists and is not empty
#   Known hashes could be used later to validate file
#

# Input Error checking
if(NOT GDML_FILE)
  message(FATAL_ERROR "no GDML_FILE argument passed")
endif()

if(NOT (EXISTS ${GDML_FILE}))
  message(FATAL_ERROR "input file '${GDML_FILE}' does not exist")
endif()

# Compare hash of empty file to input file
string(SHA1 NULL_HASH "")
file(SHA1 "${GDML_FILE}" GDML_FILE_HASH)

if(GDML_FILE_HASH STREQUAL NULL_HASH)
  message(FATAL_ERROR "File '${GDML_FILE}' exists but is of zero length")
endif()

message(STATUS "${GDML_FILE_HASH} ${GDML_FILE}")
