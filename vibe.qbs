import qbs 1.0

Project {
    name: "Vibe"

    readonly property string version: "0.9.0"

    property bool useStaticAnalyzer: false

    condition: qbs.targetOS.contains("linux") && !qbs.targetOS.contains("android")

    minimumQbsVersion: "1.9.0"

    references: [
        "declarative/hardware/hardware.qbs",
        "declarative/mpris2/mpris2.qbs",
        "declarative/networkmanager/networkmanager.qbs",
        "declarative/policykit/policykit.qbs",
        "declarative/pulseaudio/pulseaudio.qbs",

        // Vibe.KWallet no longer supported, see #17
        //"declarative/wallet/wallet.qbs",
    ]
}
