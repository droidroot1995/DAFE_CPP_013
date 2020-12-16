import qbs

CppApplication {
    consoleApplication: true
    files: [
        "main.cpp",
        "vector.cpp",
        "vector.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
