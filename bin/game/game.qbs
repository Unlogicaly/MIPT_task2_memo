import qbs

CppApplication {
    consoleApplication: true

    cpp.cxxLanguageVersion: "c++14"

    property path graph_lib_dir: "C:/Graph_lib"

    files: [
        graph_lib_dir + "/Graph.cpp",
        graph_lib_dir + "/GUI.cpp",
        graph_lib_dir + "/Window.cpp",
        "main.cpp",
    ]

    cpp.includePaths: "C:/fltk_win64/include"
    cpp.libraryPaths: "C:/fltk_win64/lib"
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
