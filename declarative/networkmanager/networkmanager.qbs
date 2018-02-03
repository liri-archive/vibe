import qbs 1.0

LiriQmlPlugin {
    name: "nmplugin"
    pluginPath: "Vibe/NetworkManager"

    Depends { name: "Qt"; submodules: ["dbus"] }
    Depends { name: "KF5"; submodules: ["NetworkManagerQt", "ModemManagerQt"] }

    condition: {
        if (!KF5.NetworkManagerQt.found)
            throw "KF5 NetworkManagerQt is required to build " + targetName;

        if (!KF5.ModemManagerQt.found)
            throw "KF5 ModemManagerQt is required to build " + targetName;

        return true;
    }

    cpp.defines: [
        'VIBE_VERSION="' + project.version + '"',
        "WITH_MODEMMANAGER_SUPPORT"
    ]

    Qt.core.enableKeywords: false

    files: ["*.cpp", "*.h", "qmldir", "plugins.qmltypes"]
}
