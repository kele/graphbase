CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

# Misc
.PHONY: clangformat
clangformat: ${CPP_SRCS} ${CPP_HDRS}
	${CLANGFORMAT} $^
