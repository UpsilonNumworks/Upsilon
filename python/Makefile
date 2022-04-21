SFLAGS += -Ipython/src
SFLAGS += -Ipython/port
SFLAGS += -I$(BUILD_DIR)/python/port
SFLAGS += -DEPSILON_VERSION="$(EPSILON_VERSION)" -DOMEGA_VERSION="$(OMEGA_VERSION)"

# How to maintain this Makefile
# - Copy PY_CORE_O_BASENAME from py.mk into py_src
# - Copy select PY_EXTMOD_O_BASENAME from py.mk into extmod_src
# - Edit special-case workarounds below as needed

py_src = $(addprefix python/src/py/,\
	mpstate.o \
        nlr.o \
        nlrx86.o \
        nlrx64.o \
        nlrthumb.o \
        nlraarch64.o \
        nlrpowerpc.o \
        nlrxtensa.o \
        nlrsetjmp.o \
        malloc.o \
        gc.o \
        pystack.o \
        qstr.o \
        vstr.o \
        mpprint.o \
        unicode.o \
        mpz.o \
        reader.o \
        lexer.o \
        parse.o \
        scope.o \
        compile.o \
        emitcommon.o \
        emitbc.o \
        asmbase.o \
        asmx64.o \
        emitnx64.o \
        asmx86.o \
        emitnx86.o \
        asmthumb.o \
        emitnthumb.o \
        emitinlinethumb.o \
        asmarm.o \
        emitnarm.o \
        asmxtensa.o \
        emitnxtensa.o \
        emitinlinextensa.o \
        emitnxtensawin.o \
        formatfloat.o \
        parsenumbase.o \
        parsenum.o \
        emitglue.o \
        persistentcode.o \
        runtime.o \
        runtime_utils.o \
        scheduler.o \
        nativeglue.o \
        pairheap.o \
        ringbuf.o \
        argcheck.o \
        warning.o \
        profile.o \
        map.o \
        obj.o \
        objarray.o \
        objattrtuple.o \
        objbool.o \
        objboundmeth.o \
        objcell.o \
        objclosure.o \
        objcomplex.o \
        objdeque.o \
        objdict.o \
        objenumerate.o \
        objexcept.o \
        objfilter.o \
        objfloat.o \
        objfun.o \
        objgenerator.o \
        objgetitemiter.o \
        objint.o \
        objint_longlong.o \
        objint_mpz.o \
        objlist.o \
        objmap.o \
        objmodule.o \
        objobject.o \
        objpolyiter.o \
        objproperty.o \
        objnone.o \
        objnamedtuple.o \
        objrange.o \
        objreversed.o \
        objset.o \
        objsingleton.o \
        objslice.o \
        objstr.o \
        objstrunicode.o \
        objstringio.o \
        objtuple.o \
        objtype.o \
        objzip.o \
        opmethods.o \
        sequence.o \
        stream.o \
        binary.o \
        builtinimport.o \
        builtinevex.o \
        builtinhelp.o \
        modarray.o \
        modbuiltins.o \
        modcollections.o \
        modgc.o \
        modio.o \
        modmath.o \
        modcmath.o \
        modmicropython.o \
        modstruct.o \
        modsys.o \
        moduerrno.o \
        modthread.o \
        vm.o \
        bc.o \
        showbc.o \
        repl.o \
        smallint.o \
        frozenmod.o \
        )

extmod_src += $(addprefix python/src/extmod/,\
  modurandom.c \
)

port_src += $(addprefix python/port/,\
  port.c \
  builtins.c \
  helpers.c \
  mod/ion/modion.cpp \
  mod/ion/modion_table.cpp \
  mod/ion/file.cpp \
  mod/kandinsky/modkandinsky.cpp \
  mod/kandinsky/modkandinsky_table.c \
  mod/matplotlib/modmatplotlib.cpp \
  mod/matplotlib/modmatplotlib_table.c \
  mod/matplotlib/pyplot/modpyplot.cpp \
  mod/matplotlib/pyplot/modpyplot_table.c \
  mod/matplotlib/pyplot/plot_controller.cpp \
  mod/matplotlib/pyplot/plot_store.cpp \
  mod/matplotlib/pyplot/plot_view.cpp \
  mod/time/modtime.c \
  mod/time/modtime_table.c \
  mod/os/modos.cpp \
  mod/os/modos_table.c \
  mod/turtle/modturtle.cpp \
  mod/turtle/modturtle_table.c \
  mod/turtle/turtle.cpp \
  mphalport.c \
)

ifeq ($(INCLUDE_ULAB), 1)
port_src += $(addprefix python/port/,\
  mod/ulab/scipy/linalg/linalg.c \
  mod/ulab/scipy/optimize/optimize.c \
  mod/ulab/scipy/signal/signal.c \
  mod/ulab/scipy/special/special.c \
  mod/ulab/ndarray_operators.c \
  mod/ulab/ulab_tools.c \
  mod/ulab/ndarray.c \
  mod/ulab/ndarray_properties.c \
  mod/ulab/numpy/approx.c \
  mod/ulab/numpy/compare.c \
  mod/ulab/ulab_create.c \
  mod/ulab/numpy/fft/fft.c \
  mod/ulab/numpy/fft/fft_tools.c \
  mod/ulab/numpy/filter.c \
  mod/ulab/numpy/linalg/linalg.c \
  mod/ulab/numpy/linalg/linalg_tools.c \
  mod/ulab/numpy/ndarray/ndarray_iter.c \
  mod/ulab/numpy/numerical.c \
  mod/ulab/numpy/poly.c \
  mod/ulab/numpy/stats.c \
  mod/ulab/numpy/transform.c \
  mod/ulab/numpy/vector.c \
  mod/ulab/numpy/numpy.c \
  mod/ulab/scipy/scipy.c \
  mod/ulab/user/user.c \
  mod/ulab/utils/utils.c \
  mod/ulab/ulab.c \
)
endif

# Workarounds

# Rename urandom to random
# In order to change the name of the micropython module 'urandom' to 'random'
# (without altering micropython files), we redefined the macro MP_QSTR_urandom
# by DMP_QSTR_random.
$(call object_for,python/src/py/objmodule.c): SFLAGS += -DMP_QSTR_urandom="MP_QSTR_random"
$(call object_for,python/src/extmod/modurandom.c): SFLAGS += -DMP_QSTR_urandom="MP_QSTR_random"

# Rename usys to sys
# In order to change the name of the micropython module 'usys' to 'sys'
# (without altering micropython files), we redefined the macro MP_QSTR_usys
# by DMP_QSTR_sys.
$(call object_for,python/src/py/objmodule.c): SFLAGS += -DMP_QSTR_usys="MP_QSTR_sys"
$(call object_for,python/src/extmod/modusys.c): SFLAGS += -DMP_QSTR_usys="MP_QSTR_sys"

# Handle upward-growing stack
# Some platforms such as emscripten have a stack that grows up. We've rewritten
# the stack control file to handle this case.
py_src := $(filter-out python/src/py/stackctrl.c, $(py_src))
port_src += python/port/stackctrl.c

# Fix the GC on emscripten
# With optimizations, register and stack variables might be held in a JavaScript
# local variables, which breaks garbage collection. Indeed, these JavaScript
# variables cannot be marked as root during garbage collection, which means that
# the heap objects they depend on will likely be destroyed. When the Python
# computing resumes, if necessary heap objects have been destroyed, the Python
# program crashes.
ifeq ($(PLATFORM),emscripten)
$(call object_for,$(py_src)): SFLAGS := $(subst -Os,-O0,$(SFLAGS))
endif

python_src = $(py_src) $(extmod_src) $(port_src)

# QSTR generation

$(eval $(call rule_for, \
  QSTRDAT, \
  python/port/genhdr/qstrdefs.generated.h, \
  python/port/genhdr/qstrdefs.in.h, \
  $$(PYTHON) python/src/py/makeqstrdata.py $$< > $$@, \
  global \
))

$(call object_for,$(python_src)): $(BUILD_DIR)/python/port/genhdr/qstrdefs.generated.h

tests_src += $(addprefix python/test/,\
  basics.cpp \
  execution_environment.cpp \
  ion.cpp \
  kandinsky.cpp \
  math.cpp \
  random.cpp \
  time.cpp \
  turtle.cpp \
  matplotlib.cpp \
)
