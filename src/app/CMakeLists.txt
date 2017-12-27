cmake_minimum_required(VERSION 2.8)
project( baseApp )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable( DEPEND_
  ${CMAKE_CURRENT_SOURCE_DIR}/src/db_orm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dependApp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_dependency-odb.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_relationship-odb.cxx
)

add_executable( INSTALL_
  ${CMAKE_CURRENT_SOURCE_DIR}/src/db_orm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/installApp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_dependency-odb.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_relationship-odb.cxx
)

add_executable( REMOVE_
  ${CMAKE_CURRENT_SOURCE_DIR}/src/db_orm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/removeApp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_dependency-odb.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_relationship-odb.cxx
)

add_executable( LIST_
  ${CMAKE_CURRENT_SOURCE_DIR}/src/db_orm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/listApp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_dependency-odb.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/include/db_relationship-odb.cxx
)

link_directories(
  /usr/lib/x86_64-linux-gnu
  /usr/local/lib
  )

target_link_libraries( DEPEND_ sqlite3 odb-sqlite odb)
target_link_libraries( INSTALL_ sqlite3 odb-sqlite odb)
target_link_libraries( REMOVE_ sqlite3 odb-sqlite odb)
target_link_libraries( LIST_ sqlite3 odb-sqlite odb)
