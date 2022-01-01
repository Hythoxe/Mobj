# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/8-10>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

cmake_minimum_required(VERSION 2.8.0)
project(SCHEMATIC)

set (CMAKE_CXX_FLAGS            "-Wall -g -std=c++11" CACHE STRING "C++ Compiler Release options." FORCE)
set (CMAKE_INSTALL_PREFIX       "../install" )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(LibXml2 REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

    # Trouver les includes de LibXml2.
   include_directories( ${SCHEMATIC_SOURCE_DIR} 
			 ${LIBXML2_INCLUDE_DIR} )

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
                                      H_files/Symbol.h
                                      H_files/Error.h
                                      H_files/Cell.h
                                      H_files/about.h
                       )

                    set( mocIncludes  H_files/SaveCellDialog.h
                                      H_files/OpenCellDialog.h
                                      H_files/CellWidget.h
                                      H_files/CellViewer.h
                                      H_files/InstancesModel.h
                                      H_files/InstancesWidget.h
                                      H_files/CellsLib.h
                                      H_files/CellsModel.h
                                      H_files/about.h
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
                                      Cpp_files/Symbol.cpp
                                      Cpp_files/Cell.cpp
                                      Cpp_files/SaveCellDialog.cpp
                                      Cpp_files/OpenCellDialog.cpp
                                      Cpp_files/CellWidget.cpp
                                      Cpp_files/CellViewer.cpp
                                      Cpp_files/InstancesModel.cpp
                                      Cpp_files/InstancesWidget.cpp
                                      Cpp_files/CellsLib.cpp
                                      Cpp_files/CellsModel.cpp
                                      Cpp_files/about.cpp
                                      Cpp_files/Main.cpp
                       )

           qt5_wrap_cpp( mocCpps      ${mocIncludes} )

         add_executable( tme810       ${cpps} ${mocCpps} )
  target_link_libraries( tme810       Qt5::Widgets ${LIBXML2_LIBRARIES} )
                install( TARGETS      tme810                      DESTINATION bin )
                install( FILES        ${includes} ${mocIncludes}  DESTINATION include )
