$(eval $(call depends_on_image,apps/home/controller.cpp,apps/external/external_icon.png))

SFLAGS += -Iapps/external/

EXTAPP_PATH ?= apps/external/app/

ifeq ($(PLATFORM),device)
# FIXME: Should be handled by Ion, since external apps are managed by Ion
	SFLAGS += -DDEVICE
else
	include $(EXTAPP_PATH)/sources.mak
endif

apps_src += $(app_external_src)

i18n_files += $(call i18n_without_universal_for,external/base)
