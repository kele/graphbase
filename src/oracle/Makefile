CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: ${Oracle_lib} ${Oracle_hdrs}

# Headers
hdrs=$(wildcard ${CUR_SRC_DIR}/%.hpp)

${Oracle_hdrs}: ${hdrs}
	touch $@

# Library
${Oracle_lib}: ${CPP_OBJECTS} ${Oracle_hdrs} | ${CUR_BUILD_DIR}
	ar rcs liboracle.a ${CPP_OBJECTS}
	mv liboracle.a $@

# Misc
.PHONY: clangformat
clangformat: ${CPP_SRCS} ${CPP_HDRS}
	${CLANGFORMAT} $^
