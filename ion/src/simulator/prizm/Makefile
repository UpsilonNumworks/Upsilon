
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
  atexit.c \
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

SFLAGS += -DFXCG50 -DTARGET_FXCG50 -m4-nofpu -mb -ffreestanding -nostdlib -Wa,--dsp -fstrict-volatile-bitfields 
LDFLAGS += -nostdlib -Wl,--no-warn-rwx-segments -T fxcg50.ld /home/heath/.local/share/fxsdk/sysroot/sh3eb-elf/lib/libgint-cg.a /home/heath/.local/share/fxsdk/sysroot/sh3eb-elf/lib/libc.a /home/heath/.local/share/fxsdk/sysroot/sh3eb-elf/lib/libgint-cg.a /home/heath/.local/share/fxsdk/sysroot/sh3eb-elf/lib/libc.a -lgcc -lopenlibm -lstdc++
#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
SFLAGS += -DM_E=2.7182818284590452354 -DM_LOG2E=1.4426950408889634074 -DM_LOG10E=0.43429448190325182765 -DM_LN2=0.69314718055994530942 -DM_LN10=2.30258509299404568402 -DM_PI=3.14159265358979323846 -DM_PI_2=1.57079632679489661923 -DM_PI_4=0.78539816339744830962 -DM_1_PI=0.31830988618379067154 -DM_2_PI=0.63661977236758134308 -DM_2_SQRTPI=1.12837916709551257390 -DM_SQRT2=1.41421356237309504880 -DM_SQRT1_2=0.70710678118654752440

SFLAGS += -include headers/include.h

# TODO: THis is bad, remove it and fix the code.
SFLAGS += -fpermissive

SFLAGS += -fno-use-cxa-atexit -gdwarf-5
LDFLAGS += -gdwarf-5
