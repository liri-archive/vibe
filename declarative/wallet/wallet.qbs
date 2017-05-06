import qbs 1.0

LiriDynamicLibrary {
    name: "Vibe.Wallet"
    targetName: "walletplugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["qml", "quick"] }
    Depends { name: "KF5.Wallet" }

    cpp.defines: base.concat(['VIBE_VERSION="' + project.version + '"'])

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
        qbs.installDir: lirideployment.qmlDir + "/Vibe/Wallet"
        fileTagsFilter: ["dynamiclibrary", "qml"]
    }
}
