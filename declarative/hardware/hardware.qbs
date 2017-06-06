import qbs 1.0

LiriQmlPlugin {
    name: "hardwareplugin"
    pluginPath: "Vibe/Hardware"

    Depends { name: "KF5.Solid" }
    Depends { name: "Fluid" }
    Depends { name: "LiriCore" }

    files: ["*.cpp", "*.h", "qmldir", "*.qmltypes"]
}
