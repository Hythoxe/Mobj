# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/4-5>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)
 
 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )


    include_directories( ${SCHEMATIC_SOURCE_DIR}
                       )

                    set( includes     H_files/Indentation.h
                                      H_files/Point.h
                                      H_files/Term.h
                                      H_files/Net.h
                                      H_files/Instance.h
                                      H_files/Node.h
                                      H_files/Cell.h
                       )

                    set( cpps         Cpp_files/Indentation.cpp
                                      Cpp_files/Point.cpp
                                      Cpp_files/Term.cpp
                                      Cpp_files/Net.cpp
                                      Cpp_files/Instance.cpp
                                      Cpp_files/Node.cpp
                                      Cpp_files/Cell.cpp
                                      Cpp_files/Main.cpp
                       )

        add_executable ( tme45        ${cpps} )
               install ( TARGETS      tme45        DESTINATION bin )
               install ( FILES        ${includes}  DESTINATION include )
