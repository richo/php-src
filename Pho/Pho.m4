AC_ARG_ENABLE(pho,
[  --enable-pho Enable a pho build],[
  PHO=$enableval
],[
  PHO=no
])

AC_MSG_CHECKING(whether to enable pho)
AC_MSG_RESULT($PHO)

if test "$PHO" = "yes"; then
  AC_DEFINE(PHO,1,[ ])
  CFLAGS="$CFLAGS -DPHO"
fi
