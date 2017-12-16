CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: ${Conversions_lib} ${Conversions_hdrs}

# Headers
${Conversions_hdrs}: ${CPP_HDRS}
	touch $@

# Library
${Conversions_lib}: ${CPP_OBJECTS} ${Conversions_hdrs} | ${CUR_BUILD_DIR}
	ar rcs libconversions.a ${CPP_OBJECTS}
	mv libconversions.a $@

# Misc
.PHONY: clangformat
clangformat: ${CPP_SRCS} ${CPP_HDRS}
	${CLANGFORMAT} $^
