
ion_src += $(addprefix ion/src/simulator/prizm/, \
  main.cpp \
  clipboard.cpp \
  display.cpp \
  framebuffer.cpp \
  telemetry_init.cpp \
  keyboard.cpp \
  events_keyboard.cpp \
  events.cpp \
  timing.cpp \
  console.cpp \
  backlight.cpp \
)

liba_src += $(addprefix liba/src/, \
  strlcat.c \
  strlcpy.c \
)

ion_src += ion/src/shared/collect_registers.cpp

sdl_simu_needs_to_be_removed += $(addprefix ion/src/simulator/shared/, \
  main.cpp \
  clipboard.cpp \
  display.cpp \
  framebuffer.cpp \
  keyboard.cpp \
  events_keyboard.cpp \
  events_platform.cpp \
  events.cpp \
  layout.cpp \
  actions.cpp \
  window.cpp \
  timing.cpp \
  console.cpp \
)

sdl_simu_needs_to_be_removed += $(addprefix ion/src/shared/dummy/, \
  backlight.cpp \
)

#sdl_simu_needs_to_be_removed += $(addprefix ion/src/simulator/shared/dummy/, \
#  display.cpp \
#  led.cpp \
#  usb.cpp \
#  battery.cpp \
#  store_script.cpp \
#)

# Remove the dummy diplay (re-implemented) and the SDL simulator stuff.
ion_src := $(filter-out $(sdl_simu_needs_to_be_removed),$(ion_src))

SFLAGS := $(filter-out -Iion/src/simulator/external/sdl/include,$(SFLAGS))

SFLAGS += -DFXCG50 -DTARGET_FXCG50 -m4-nofpu -mb -ffreestanding -nostdlib -Wa,--dsp -fstrict-volatile-bitfields -g
LDFLAGS += -nostdlib -Wl,--no-warn-rwx-segments -T fxcg50.ld -lgint-cg -lc -lgint-cg -lc -lgcc -lopenlibm -lstdc++
