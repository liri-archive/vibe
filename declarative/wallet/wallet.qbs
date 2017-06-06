import qbs 1.0

LiriQmlPlugin {
    name: "walletplugin"
    pluginPath: "Vibe/Wallet"

    Depends { name: "KF5.Wallet" }

    cpp.defines: base.concat(['VIBE_VERSION="' + project.version + '"'])

    files: ["*.cpp", "*.h", "qmldir", "*.qmltypes"]
}
