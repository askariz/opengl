SET(SEARCH_PATH /usr/include)

FIND_PATH(GLM_INCLUDE_PATH glm/glm.hpp ${SEARCH_PATH})

message("Find GLM path" ${GLM_PATH})

