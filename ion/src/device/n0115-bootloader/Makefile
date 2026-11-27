ion_device_src += $(addprefix ion/src/device/n0110/drivers/, \
  cache.cpp \
  led.cpp \
  reset.cpp \
  usb.cpp \
)

ion_device_src += $(addprefix ion/src/device/n0115/drivers/, \
  fccid.cpp \
)

ion_device_src += $(addprefix ion/src/device/n0110-bootloader/drivers/, \
  board.cpp \
  external_flash_tramp.cpp \
  power.cpp \
  trampoline.cpp \
)

ion_device_src += $(addprefix ion/src/device/n0110-bootloader/boot/, \
  rt0.cpp \
)

ion_device_src += $(addprefix ion/src/device/n0110-bootloader/, \
  platform_info.cpp \
)

$(call object_for,ion/src/device/n0110-bootloader/platform_info.cpp): CXXFLAGS += $(snapshot_includes) -DAPPS_CONTAINER_APPS_DECLARATION="$(apps_declaration)" -DAPPS_CONTAINER_SNAPSHOT_DECLARATIONS="$(snapshots_declaration)" -DAPPS_CONTAINER_SNAPSHOT_CONSTRUCTORS="$(snapshots_construction)" -DAPPS_CONTAINER_SNAPSHOT_LIST="$(snapshots_list)" -DAPPS_CONTAINER_SNAPSHOT_COUNT=$(snapshots_count) -DEPSILON_APPS_NAMES=$(epsilon_app_names)

LDSCRIPT ?= ion/src/device/n0110-bootloader/flash.ld
