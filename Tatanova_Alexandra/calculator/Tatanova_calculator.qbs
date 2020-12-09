import qbs

CppApplication {
    consoleApplication: true
    files: [
        "Token.cpp",
        "Token.h",
        "Variable.cpp",
        "Variable.h",
        "main.cpp",
        "std_lib_facilities.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
