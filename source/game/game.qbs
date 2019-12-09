import qbs

CppApplication {
    consoleApplication: true

    cpp.cxxLanguageVersion: "c++14"

    property path graph_lib_dir: "..\\..\\Graph_lib"
    property path fltk_dir: "..\\..\\fltk"

    files: [
        "card.cpp",
        "card.h",
        "field.cpp",
        "field.h",
        "game_paths.cpp",
        "game_paths.h",
        "game_start.cpp",
        "game_start.h",
        "modechoose.cpp",
        "modechoose.h",
        "mywin.cpp",
        "mywin.h",
        "playagain.cpp",
        "playagain.h",
        graph_lib_dir + "\\Graph.cpp",
        graph_lib_dir + "\\GUI.cpp",
        graph_lib_dir + "\\Window.cpp",
        "split.h",
        "split.cpp",
        "main.cpp",
        "pictures_treatment.h",
        "pictures_treatment.cpp",
        "editting_files.h",
        "editting_files.cpp",
        "tracer.h",
        "tracer.cpp",
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
