##### 
#
# SYNOPSIS
#
#   AX_PATH_QMAKE4
#
# DESCRIPTION
#
#   Check for Qt4 version of qmake.
#
#   $QMAKE4 is set to absolute name of the executable if found.
#
# LAST MODIFICATION
#
#   2007-09-30
#
# COPYLEFT
#
#   Copyright (c) 2007 YAMAMOTO Kengo <yamaken AT bp.iij4u.or.jp>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_PATH_QMAKE4], [
  ax_guessed_qt4_dirs="/usr/lib/qt4/bin:/usr/local/lib/qt4/bin:/usr/qt4/bin:/usr/local/qt4/bin:${QT4DIR}/bin:${QTDIR}/bin"
  AC_PROG_EGREP
  AC_PATH_PROGS(_QMAKE4, [qmake-qt4 qmake4], [], ["$PATH:$ax_guessed_qt4_dirs"])
  AC_PATH_PROGS(_QMAKE, [qmake], [], ["$PATH:$ax_guessed_qt4_dirs"])

  AC_CACHE_CHECK([for Qt4 version of qmake], ax_cv_path_QMAKE4, [
    ax_cv_path_QMAKE4=no
    for qmake4 in ${_QMAKE4} ${_QMAKE}; do
      if ($qmake4 --version 2>&1 | $EGREP -q 'Qt.*[[Vv]]ersion 4'); then
        QMAKE4="$qmake4"
        ax_cv_path_QMAKE4="$qmake4"
	break
      fi
    done
  ])
  AC_SUBST([QMAKE4])
])
