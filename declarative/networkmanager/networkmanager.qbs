import qbs 1.0

LiriDynamicLibrary {
    name: "Vibe.NetworkManager"
    targetName: "nmplugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["dbus", "qml", "quick"] }
    Depends { name: "KF5"; submodules: ["NetworkManagerQt", "ModemManagerQt"] }

    cpp.defines: [
        'VIBE_VERSION="' + project.version + '"',
        "WITH_MODEMMANAGER_SUPPORT"
    ]

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
        qbs.installDir: lirideployment.qmlDir + "/Vibe/NetworkManager"
        fileTagsFilter: ["dynamiclibrary", "qml"]
    }
}
