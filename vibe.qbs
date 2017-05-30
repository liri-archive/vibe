import qbs 1.0

Project {
    name: "Vibe"

    readonly property string version: "0.9.0"

    condition: qbs.targetOS.contains("linux")

    minimumQbsVersion: "1.8"

    qbsSearchPaths: ["qbs/shared"]

    references: [
        "declarative/hardware/hardware.qbs",
        "declarative/mpris2/mpris2.qbs",
        "declarative/networkmanager/networkmanager.qbs",
        "declarative/policykit/policykit.qbs",
        "declarative/pulseaudio/pulseaudio.qbs",
        "declarative/wallet/wallet.qbs",
    ]
}
