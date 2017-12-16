CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: ${Sources_lib} ${Sources_hdrs}

# Headers
${Sources_hdrs}: ${CPP_HDRS}
	touch $@

# Library
${Sources_lib}: ${CPP_OBJECTS} ${Sources_hdrs} | ${CUR_BUILD_DIR}
	ar rcs libsources.a ${CPP_OBJECTS}
	mv libsources.a $@

# Misc
.PHONY: clangformat
clangformat: ${CPP_SRCS} ${CPP_HDRS}
	${CLANGFORMAT} $^
