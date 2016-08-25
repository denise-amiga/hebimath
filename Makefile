# hebimath - arbitrary precision arithmetic library
# See LICENSE file for copyright and license details

CONFIG := config.mk
include $(CONFIG)

KERN_generic := generic
KERN_x86_64 := x86_64

KERN_auto != sh -c 'uname -m 2>/dev/null || \
	echo generic | sed -e ''s/i.86$$/i386/'''

KERN_detected != sh -c 'test -d src/p/$(KERN_$(KERN)) && \
	echo $(KERN_$(KERN)) || echo generic'

KERNMV_generic := fixed
KERNMV_x86_64 := $(KERNMV)
KERNMV_detected := $(KERNMV_$(KERN_detected))

PKERNELS := \
	padd \
	paddu \
	pclz \
	pcmp \
	pcopy \
	pctz \
	pdivmod_norm \
	pdivmodu \
	pmove \
	pmul \
	pmulu \
	pnorm \
	pshl \
	pshr \
	psqr \
	psub \
	psubu \
	pzero

PKERNELS_dynamic := $(PKERNELS:%=p/dynamic/%)

PFUNCTIONS := \
	p/palloc \
	p/palloc_cb \
	p/pfree \
	p/pfree_cb \
	p/pdivmod \
	p/pmul_karatsuba \
	p/pmul_karatsuba_space \
	p/prand_kiss \
	p/precipu_lut \
	p/psetu \
	p/psetzero \
	p/psqr_karatsuba \
	p/psqr_karatsuba_space \
	$(PKERNELS_$(KERNMV_detected)) \
	$(PKERNELS:%=p/$(KERN_detected)/%)

ZFUNCTIONS := \
	z/zinit \
	z/zinits \
	z/zinitn \
	z/zinit_allocator \
	z/zinit_buffer \
	z/zinit_reserve \
	z/zinit_copy \
	z/zinit_copy_buffer \
	z/zinit_copy_reserve \
	z/zinit_move \
	z/zdestroy \
	z/zdestroys \
	z/zdestroyn \
	z/zrealloc \
	z/zrealloczero \
	z/zreserve \
	z/zshrink \
	z/zswap \
	z/zallocator \
	z/zcapacity \
	z/zused \
	z/zsign \
	z/zzero \
	z/zeven \
	z/zodd \
	z/zbits \
	z/zcmpmag \
	z/zcmp \
	z/zset \
	z/zset_copy \
	z/zset_move \
	z/zseti \
	z/zsetu \
	z/zsetzero \
	z/zsetstr \
	z/zgeti \
	z/zgetu \
	z/zgetsi \
	z/zgetsu \
	z/zgetstr \
	z/zabs \
	z/zneg \
	z/zadd \
	z/zsub \
	z/zmul \
	z/zsqr \
	z/zaddi \
	z/zaddu \
	z/zsubi \
	z/zsubu \
	z/zmuli \
	z/zmulu \
	z/zdivi \
	z/zdivu \
	z/zdivmodi \
	z/zdivmodu \
	z/zmodi \
	z/zmodu \
	z/zshl \
	z/zshr \
	z/zrand_kiss

FUNCTIONS := \
	$(PFUNCTIONS) \
	$(ZFUNCTIONS) \
	error_handler \
	error_jmp \
	error_save \
	error_restore \
	error_last \
	error_raise \
	alloc \
	alloc_cb \
	free \
	free_cb

MODULES_dynamic := hwcaps

MODULES := \
	alloc_get \
	alloc_set \
	alloc_table \
	context \
	$(MODULES_$(KERNMV_detected))

SRC := $(FUNCTIONS) $(MODULES)

CFG_TARGETS_generic := config.h
CFG_TARGETS_x86_64 := config.h config.inc

DEPS_generic := config.h src/p/generic/generic.h
DEPS_x86_64 := config.h config.inc src/p/x86_64/x86_64.inc
DEPS := $(CONFIG) hebimath.h internal.h $(DEPS_$(KERN_detected))

OBJ_shared := $(SRC:%=src/%.po)
OBJ_static := $(SRC:%=src/%.o)

LIBS_both := libhebimath.so libhebimath.a
LIBS_shared := libhebimath.so
LIBS_static := libhebimath.a
LIBS := $(LIBS_$(LINKAGE))

TEST_LDLIBS_both := libhebimath.a
TEST_LDLIBS_shared := -lhebimath
TEST_LDLIBS_static := libhebimath.a
TEST_LDLIBS := $(TEST_LDLIBS_$(LINKAGE))

BENCH_P := \
	padd \
	paddu \
	pclz \
	pcmp \
	pcopy \
	pdivmodu \
	pmove \
	pmul \
	pmul_karatsuba \
	pmulu \
	pnorm \
	pshl \
	pshr \
	psqr \
	psqr_karatsuba \
	psub \
	psubu \
	pzero

BENCH_P_BIN := $(BENCH_P:%=bench/p/%)
BENCH_BIN := $(BENCH_P_BIN)
BENCH_OBJ := bench/bench.o
BENCH_DEPS := $(DEPS) bench/bench.h

CHECK_P := \
	pcmp \
	pcopy \
	pnorm \
	pzero

CHECK_Z := \
	zgetset \
	zaddi \
	zsubi \
	zmuli \
	zadd \
	zsub \
	zmul \
	zshl \
	zshr

CHECK_SRC := \
	check \
	bc \
	zcheckbinop \
	zcheckbinopi64 \
	zpermutation

CHECK_P_BIN := $(CHECK_P:%=check/p/%)
CHECK_Z_BIN := $(CHECK_Z:%=check/z/%)
CHECK_BIN := $(CHECK_P_BIN) $(CHECK_Z_BIN)
CHECK_OBJ := $(CHECK_SRC:%=check/%.o)
CHECK_DEPS := $(DEPS) check/check.h

Q_ := @
Q_0 := @
Q := $(Q_$(V))

.SUFFIXES:
.SUFFIXES: .c .s .o .po

.PHONY: all config check check/p check/z \
	clean scrub dist install uninstall options

all: $(LIBS)

config: $(CFG_TARGETS_$(KERN_detected))

config.h:
	@echo copying $@ from config.def.h
	$(Q)cp config.def.h $@

config.inc:
	@echo copying $@ from config.def.$(KERN_detected).inc
	$(Q)cp config.def.$(KERN_detected).inc $@

hebimath.h: hebimath.h.in
	@echo generating $@ from hebimath.h.in
	$(Q)awk -v p='$(KERNMV_detected)|$(SIMD)' \
	    '$$1==">>>"{x=$$2!~p;next;} \
	     $$1=="<<<"{x=0;next;} \
	     !x{print $$0}' \
	     <hebimath.h.in >$@

libhebimath.so: $(DEPS) $(OBJ_shared)
	@echo LD $@
	$(Q)$(CC) $(LDFLAGS_shared) -o $@ $(LDFLAGS) $(OBJ_shared) $(LDLIBS)

libhebimath.a: $(DEPS) $(OBJ_static)
	@echo AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $(OBJ_static)
	$(Q)$(RANLIB) $@

bench: $(BENCH_BIN)
	@sh runtests.sh "bench" $(BENCH_BIN)

bench/p: $(BENCH_BIN)
	@sh runtests.sh "bench/p" $(BENCH_P_BIN)

$(BENCH_BIN): $(BENCH_DEPS) $(LIBS) bench/libbench.a
	@echo CC $@.c
	$(Q)$(CC) -o $@ $(CFLAGS_static) $(CFLAGS) \
		$(CPPFLAGS_static) $(CPPFLAGS) $@.c \
		$(LDFLAGS) -L. bench/libbench.a $(TEST_LDLIBS) $(LDLIBS)

bench/libbench.a: $(BENCH_DEPS) $(BENCH_OBJ)
	@echo AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $(BENCH_OBJ)
	$(Q)$(RANLIB) $@

check: $(CHECK_BIN)
	@sh runtests.sh "check" $(CHECK_BIN)

check/p: $(CHECK_P_BIN)
	@sh runtests.sh "check/p" $(CHECK_P_BIN)

check/z: $(CHECK_Z_BIN)
	@sh runtests.sh "check/z" $(CHECK_Z_BIN)

$(CHECK_BIN): $(CHECK_DEPS) $(LIBS) check/libcheck.a
	@echo CC $@.c
	$(Q)$(CC) -o $@ $(CFLAGS_static) $(CFLAGS) \
		$(CPPFLAGS_static) $(CPPFLAGS) $@.c \
		$(LDFLAGS) -L. check/libcheck.a $(TEST_LDLIBS) $(LDLIBS)

check/libcheck.a: $(CHECK_DEPS) $(CHECK_OBJ)
	@echo AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $(CHECK_OBJ)
	$(Q)$(RANLIB) $@

.c.po: $(DEPS)
	@echo CC $<
	$(Q)$(CC) -o $@ -c $(CFLAGS_shared) $(CFLAGS) \
		$(CPPFLAGS_shared) $(CPPFLAGS) $<

.c.o: $(DEPS)
	@echo CC $<
	$(Q)$(CC) -o $@ -c $(CFLAGS_static) $(CFLAGS) \
		$(CPPFLAGS_static) $(CPPFLAGS) $<

.s.po: $(DEPS)
	@echo AS $<
	$(Q)$(AS) -o $@ $(ASFLAGS_$(KERNMV_detected)) \
		$(ASFLAGS_shared) $(ASFLAGS) $<
	$(Q)$(STRIP) -o $@ -x $@

.s.o: $(DEPS)
	@echo AS $<
	$(Q)$(AS) -o $@ $(ASFLAGS_$(KERNMV_detected)) \
		$(ASFLAGS_static) $(ASFLAGS) $<
	$(Q)$(STRIP) -o $@ -x $@

clean:
	@echo cleaning
	$(Q)rm -f hebimath.h $(LIBS_both) $(OBJ_shared) $(OBJ_static) \
		bench/libbench.a check/libcheck.a $(CHECK_BIN) $(CHECK_OBJ)

scrub: clean
	@echo scrubbing
	$(Q)rm -f config.h config.inc *.tar.xz
	$(Q)find bench -type f -name "*.o" -exec rm -f {} \;
	$(Q)find bench -type f -name "*.po" -exec rm -f {} \;
	$(Q)find bench -type f -name "*.lst" -exec rm -f {} \;
	$(Q)find bench -type f -perm -0100 -exec rm -f {} \;
	$(Q)find check -type f -name "*.o" -exec rm -f {} \;
	$(Q)find check -type f -name "*.po" -exec rm -f {} \;
	$(Q)find check -type f -name "*.lst" -exec rm -f {} \;
	$(Q)find check -type f -perm -0100 -exec rm -f {} \;
	$(Q)find src -type f -name "*.o" -exec rm -f {} \;
	$(Q)find src -type f -name "*.po" -exec rm -f {} \;
	$(Q)find src -type f -name "*.lst" -exec rm -f {} \;

dist: scrub
	@echo creating dist tarball
	$(Q)mkdir -p hebimath-$(VERSION)
	$(Q)cp -R -t hebimath-$(VERSION) LICENSE README Makefile \
		config.def.h config.def.x86_x64.inc config.mk \
		hebimath.h.in internal.h bench check src
	$(Q)tar -cJf hebimath-$(VERSION).tar.xz hebimath-$(VERSION)
	$(Q)rm -rf hebimath-$(VERSION)

install: all
	@echo installing header files to $(DESTDIR)$(PREFIX)/include
	$(Q)mkdir -p $(DESTDIR)$(PREFIX)/include
	$(Q)cp -f hebimath.h $(DESTDIR)$(PREFIX)/include
	$(Q)chmod 644 $(DESTDIR)$(PREFIX)/include/hebimath.h
	@echo installing library files to $(DESTDIR)$(PREFIX)/lib
	$(Q)mkdir -p $(DESTDIR)$(PREFIX)/lib
	$(Q)cp -f libhebimath.a $(DESTDIR)$(PREFIX)/lib
	$(Q)chmod 644 $(DESTDIR)$(PREFIX)/lib/libhebimath.a
	$(Q)cp -f libhebimath.so $(DESTDIR)$(PREFIX)/lib
	$(Q)chmod 755 $(DESTDIR)$(PREFIX)/lib/libhebimath.so

uninstall:
	@echo removing header files from $(DESTDIR)$(PREFIX)/lib
	$(Q)rm -f $(DESTDIR)$(PREFIX)/include/hebimath.h
	@echo removing library files from $(DESTDIR)$(PREFIX)/lib
	$(Q)rm -f $(DESTDIR)$(PREFIX)/lib/libhebimath.a
	$(Q)rm -f $(DESTDIR)$(PREFIX)/lib/libhebimath.so

options:
	@echo libhebimath build options:
	@echo "LINKAGE           = $(LINKAGE)"
	@echo "KERN              = $(KERN_detected)"
	@echo "KERNMV            = $(KERNMV_detected)"
	@echo "SIMD              = $(SIMD)"
	@echo "CPPFLAGS          = $(CPPFLAGS)"
	@echo "CFLAGS            = $(CFLAGS)"
	@echo "ASFLAGS           = $(ASFLAGS)"
	@echo "ARFLAGS           = $(ARFLAGS)"
	@echo "LDFLAGS           = $(LDFLAGS)"
	@echo "CC                = $(CC)"
	@echo "AS                = $(AS)"
	@echo "AR                = $(AR)"
	@echo "STRIP             = $(STRIP)"
