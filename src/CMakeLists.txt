add_library(spferr spferr.c)
target_include_directories(spferr PUBLIC ${SPF_SOURCE_DIR}/include)

add_library(spfexpression expression.c)
target_include_directories(spfexpression PUBLIC ${SPF_SOURCE_DIR}/include)
target_link_libraries(spfexpression spferr)

add_library(spfdensities densities.c)
target_include_directories(spfdensities PUBLIC ${SPF_SOURCE_DIR}/include)
target_link_libraries(spfdensities m)

add_library(spfparam param.c)
target_include_directories(spfparam PUBLIC ${SPF_SOURCE_DIR}/include)
target_link_libraries(spfparam spferr)

add_library(spfderivatives derivatives.c)
target_include_directories(spfderivatives PUBLIC ${SPF_SOURCE_DIR}/include)
target_link_libraries(spfderivatives spfparam spfexpression)

# main encapsulating library
add_library(spf distribution.c)
target_include_directories(spf PUBLIC ${SPF_SOURCE_DIR}/include)
target_link_libraries(spf spfparam spferr spfdensities spfexpression spfderivatives)

add_executable(driver driver.c)
target_include_directories(driver PUBLIC ${SPF_SOURCE_DIR}/include)
target_link_libraries(driver spf)
