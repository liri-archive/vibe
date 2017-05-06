import qbs 1.0

LiriDynamicLibrary {
    name: "Vibe.PulseAudio"
    targetName: "pulseaudioplugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["qml", "quick"] }
    Depends { name: "PulseAudio" }

    cpp.defines: ['VIBE_VERSION="' + project.version + '"']
    cpp.includePaths: base.concat(["qpulseaudio"])

    files: ["*.cpp", "*.h", "qpulseaudio/*.cpp", "qpulseaudio/*.h"]

    Group {
        name: "QML Files"
        files: [
            "*.qml",
            "qmldir",
            "plugins.qmltypes"
        ]
        fileTags: ["qml"]
    }

    Group {
        qbs.install: true
        qbs.installDir: lirideployment.qmlDir + "/Vibe/PulseAudio"
        fileTagsFilter: ["dynamiclibrary", "qml"]
    }
}
