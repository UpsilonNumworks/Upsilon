
ion_device_src += $(addprefix ion/src/device/bootloader/drivers/, \
  board.cpp \
  cache.cpp \
  external_flash_tramp.cpp \
  led.cpp \
  power.cpp \
  reset.cpp \
  trampoline.cpp \
  usb.cpp \
)

ion_device_src += $(addprefix ion/src/device/bootloader/boot/, \
  rt0.cpp \
)

ion_device_src += $(addprefix ion/src/device/bootloader/, \
  platform_info.cpp \
)

ion_device_src += $(addprefix ion/src/device/n0110/drivers/, \
  fccid.cpp \
)

$(call object_for,ion/src/device/bootloader/platform_info.cpp): CXXFLAGS += $(snapshot_includes) -DAPPS_CONTAINER_APPS_DECLARATION="$(apps_declaration)" -DAPPS_CONTAINER_SNAPSHOT_DECLARATIONS="$(snapshots_declaration)" -DAPPS_CONTAINER_SNAPSHOT_CONSTRUCTORS="$(snapshots_construction)" -DAPPS_CONTAINER_SNAPSHOT_LIST="$(snapshots_list)" -DAPPS_CONTAINER_SNAPSHOT_COUNT=$(snapshots_count) -DEPSILON_APPS_NAMES=$(epsilon_app_names)
