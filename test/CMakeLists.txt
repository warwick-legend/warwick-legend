# 1. Check that we can run the most trivial example
add_test(NAME minimal-run COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test0.mac")

# 2. Check geometry can be switched
add_test(NAME swap-geometry COMMAND warwick-legend -m "${CMAKE_CURRENT_LIST_DIR}/test-swap-geometry.mac")