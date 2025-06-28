#!/bin/bash
DYLD_FRAMEWORK_PATH=/opt/homebrew/Cellar/qt@5/5.15.16_2/lib${DYLD_FRAMEWORK_PATH:+:$DYLD_FRAMEWORK_PATH}
export DYLD_FRAMEWORK_PATH
QT_PLUGIN_PATH=/opt/homebrew/Cellar/qt@5/5.15.16_2/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"
