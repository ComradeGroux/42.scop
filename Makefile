CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Werror -Iheaders -Ilibs/glfw/include -Ilibs/glad
LDFLAGS := -lGL -lglfw -ldl -lpthread -lm -lX11

SRC_DIR := srcs
BUILD_DIR := build
OBJS_DIR := objs
GLFW_DIR := libs/glfw-3.4
GLFW_BUILD_DIR := $(BUILD_DIR)/glfw

TARGET := scop

SRCS := $(wildcard $(SRC_DIR)/*.cpp) \
		libs/glad/glad.c

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/$(OBJS_DIR)/%.o)

GLFW_LIB := $(GLFW_BUILD_DIR)/src/libglfw3.a

all: $(TARGET)

$(TARGET): $(OBJS) $(GLFW_LIB)
	@echo "→ Edition de liens de $(TARGET)"
	$(CXX) $(OBJS) $(GLFW_LIB) $(LDFLAGS) -o $@

$(BUILD_DIR)/$(OBJS_DIR)%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(OBJS_DIR)
	@echo "→ Compilation de $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLFW_LIB):
	@echo "→ Compilation de GLFW"
	@mkdir -p $(GLFW_BUILD_DIR)
	cd $(GLFW_BUILD_DIR) && cmake -DBUILD_SHARED_LIBS=OFF ../../$(GLFW_DIR)
	$(MAKE) -C $(GLFW_BUILD_DIR)

clean:
	@echo "→ Nettoyage..."
	rm -rf $(BUILD_DIR)/$(OBJS_DIR)

fullclean:
	@echo "→ Nettoyage complet"
	rm -rf $(BUILD_DIR)/

fclean: fullclean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fullclean fclean re