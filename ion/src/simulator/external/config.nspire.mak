
undefine sdl_src
undefine ion_simulator_sdl_src

sdl_src += $(addprefix ion/src/simulator/external/n2DLib/, \
  n2DLib.c \
)

SFLAGS += -Iion/src/simulator/external/n2DLib
