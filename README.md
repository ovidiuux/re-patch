# GTA: VC 1.12 Android Debug - arm64-v8a Patch

This project provides a native code patch for Grand Theft Auto: Vice City (v1.12) on Android devices. 
The patch hooks into the game's debug logging system to provide enhanced logging capabilities through Android's logcat system.

adb logcat -s "re-patch" "NVEvent" "libGTAVC" "DEBUG" "OSWrapper"
