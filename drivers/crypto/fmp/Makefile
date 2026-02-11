# Exynos FMP makefile

obj-$(CONFIG_EXYNOS_FMP) += fmp-core.o
fmp-core-$(CONFIG_EXYNOS_FMP_FIPS) += $(FIPS_PR)fmp.o \
				$(FIPS_PR)fmp_test.o \
				$(FIPS_PR)fmp_fips_main.o \
				$(FIPS_PR)fmp_fips_selftest.o \
				$(FIPS_PR)hmac-sha256.o \
				$(FIPS_PR)fmp_fips_cipher.o \
				$(FIPS_PR)sha256.o

.PHONY: fips_clean
fips_clean:
	@echo " Clean FIPS module artefacts .... "
	@rm -f $(objtree)/drivers/crypto/fmp/*.o
	@echo " Clean FIPS module artefacts completed "
