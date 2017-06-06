import qbs 1.0

LiriQmlPlugin {
    name: "nmplugin"
    pluginPath: "Vibe/NetworkManager"

    Depends { name: "Qt"; submodules: ["dbus"] }
    Depends { name: "KF5"; submodules: ["NetworkManagerQt", "ModemManagerQt"] }

    cpp.defines: [
        'VIBE_VERSION="' + project.version + '"',
        "WITH_MODEMMANAGER_SUPPORT"
    ]

    Qt.core.enableKeywords: false

    files: ["*.cpp", "*.h", "qmldir", "plugins.qmltypes"]
}
