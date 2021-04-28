# 1. Check that we can run the most trivial example
add_test(NAME minimal-run COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test0.mac")

# 2. Check geometry can be switched
add_test(NAME swap-geometry COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-swap-geometry.mac")

# 3. Check bias can be switched
add_test(NAME change-bias COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-change-bias.mac")

# 4. Check trajectory storage runs
add_test(NAME trajectory-storage COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-store-trajectory.mac")

# 5. Check gdml export runs
# a. File output
add_test(NAME gdml-export-run COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-gdml-export-run.mac")
# b. File existence (*not* validation)
add_test(NAME gdml-export-exists
  COMMAND ${CMAKE_COMMAND} -DGDML_FILE=${CMAKE_CURRENT_BINARY_DIR}/test-gdml-export.gdml
                           -P "${CMAKE_CURRENT_LIST_DIR}/test-gdml-export-exists.cmake")
set_property(TEST gdml-export-exists PROPERTY DEPENDS gdml-export-run)
