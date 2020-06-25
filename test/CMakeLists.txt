# 1. Check that we can run the most trivial example
add_test(NAME minimal-run COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test0.mac")

# 2. Check geometry can be switched
add_test(NAME swap-geometry COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-swap-geometry.mac")

# 3. Check bias can be switched
add_test(NAME change-bias COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-change-bias.mac")

# 4. Check trajectory storage runs
add_test(NAME trajectory-storage COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-trajectory-storage.mac")

