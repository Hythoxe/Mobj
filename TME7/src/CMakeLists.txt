# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/7>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)
 
 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

# Detection de LibXml2.
    find_package(LibXml2)

# Trouver les includes de LibXml2.
    include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR} )
                       

                    set( includes     H_files/XmlUtil.h
                                      H_files/Indentation.h
                                      H_files/Point.h
                                      H_files/Term.h
                                      H_files/Net.h
                                      H_files/Instance.h
                                      H_files/Node.h
                                      H_files/Box.h
                                      H_files/Line.h
                                      H_files/LineShape.h
                                      H_files/BoxShape.h
                                      H_files/EllipseShape.h
                                      H_files/ArcShape.h
                                      H_files/TermShape.h
                                      H_files/Shape.h
                                      #H_files/Symbol.h
                                      H_files/Cell.h
                       )
                       
                    set( cpps         Cpp_files/XmlUtil.cpp
                                      Cpp_files/Indentation.cpp
                                      Cpp_files/Point.cpp
                                      Cpp_files/Term.cpp
                                      Cpp_files/Net.cpp
                                      Cpp_files/Instance.cpp
                                      Cpp_files/Node.cpp
                                      Cpp_files/Box.cpp
                                      Cpp_files/Line.cpp
                                      Cpp_files/LineShape.cpp
                                      Cpp_files/BoxShape.cpp
                                      Cpp_files/EllipseShape.cpp
                                      Cpp_files/ArcShape.cpp
                                      Cpp_files/TermShape.cpp
                                      Cpp_files/Shape.cpp
                                      #Cpp_files/Symbol.cpp
                                      Cpp_files/Cell.cpp
                                      Cpp_files/Main.cpp
                       )

# Faire l'edition de liens avec la LibXml2
        add_executable ( tme7        ${cpps} )
        target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
               install ( TARGETS      tme7        DESTINATION bin )
               install ( FILES        ${includes}  DESTINATION include )
