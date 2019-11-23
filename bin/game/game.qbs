import qbs

CppApplication {
    consoleApplication: true

    cpp.cxxLanguageVersion: "c++14"

    property path graph_lib_dir: "..\\..\\Graph_lib"
    property path fltk_dir: "..\\..\\fltk"

    files: [
        graph_lib_dir + "\\Graph.cpp",
        graph_lib_dir + "\\GUI.cpp",
        graph_lib_dir + "\\Window.cpp",
        "grid.h",
        "grid.cpp",
        "create_window.h",
        "create_window.cpp",
        "split.h",
        "split.cpp",
        "main.cpp",
    ]

    cpp.includePaths:  fltk_dir + "\\include"
    cpp.libraryPaths: fltk_dir + "\\lib"

    cpp.cxxFlags: "-Wno-unused-parameter"

    cpp.driverLinkerFlags: "-mwindows"

    cpp.staticLibraries: [
        "fltk_images",
        "fltk",
        "fltk_png",
        "z",
        "fltk_jpeg",
        "ole32",
        "uuid",
        "comctl32",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
