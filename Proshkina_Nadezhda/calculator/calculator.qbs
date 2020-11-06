import qbs

CppApplication {
    consoleApplication: true
    files: [
        "Test",
        "Test_out",
        "Token.cpp",
        "Token.h",
        "Variable.cpp",
        "Variable.h",
        "calculate.h",
        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
