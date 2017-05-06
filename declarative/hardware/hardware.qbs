import qbs 1.0

LiriDynamicLibrary {
    name: "Vibe.Hardware"
    targetName: "hardwareplugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["qml", "quick"] }
    Depends { name: "KF5.Solid" }
    Depends { name: "Fluid" }
    Depends { name: "LiriCore" }

    files: ["*.cpp", "*.h"]

    Group {
        name: "QML Files"
        files: [
            "qmldir",
            "plugins.qmltypes"
        ]
        fileTags: ["qml"]
    }

    Group {
        qbs.install: true
        qbs.installDir: lirideployment.qmlDir + "/Vibe/Hardware"
        fileTagsFilter: ["dynamiclibrary", "qml"]
    }
}
