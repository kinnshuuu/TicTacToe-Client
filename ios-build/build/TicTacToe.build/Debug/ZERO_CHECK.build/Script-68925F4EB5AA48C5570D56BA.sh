#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/kinshujain/Desktop/TicTacToe/ios-build
  make -f /Users/kinshujain/Desktop/TicTacToe/ios-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/kinshujain/Desktop/TicTacToe/ios-build
  make -f /Users/kinshujain/Desktop/TicTacToe/ios-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/kinshujain/Desktop/TicTacToe/ios-build
  make -f /Users/kinshujain/Desktop/TicTacToe/ios-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/kinshujain/Desktop/TicTacToe/ios-build
  make -f /Users/kinshujain/Desktop/TicTacToe/ios-build/CMakeScripts/ReRunCMake.make
fi

