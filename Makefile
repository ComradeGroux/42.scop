CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Werror -Iheaders -Ilibs/glfw/include -Ilibs/glad/include/glad -g
LDFLAGS := -lGL -lglfw -ldl -lpthread -lm -lX11

SRC_DIR := srcs
BUILD_DIR := build
OBJS_DIR := $(BUILD_DIR)/objs
LIB_DIR := libs
GLFW_DIR := $(LIB_DIR)/glfw-3.4
GLFW_BUILD_DIR := $(BUILD_DIR)/glfw

TARGET := scop

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJS_DIR)/%.o)

GLFW_DEP_DIR := $(LIB_DIR)/glfw
GLFW_BUILD_DIR := $(BUILD_DIR)/glfw
GLFW_LIB := $(GLFW_BUILD_DIR)/src/libglfw3.a

GLAD_BUILD_DIR := $(LIB_DIR)/glad
GLAD_OBJ := $(OBJS_DIR)/glad.o

all: $(TARGET)

$(TARGET): $(GLFW_LIB) $(GLAD_OBJ) $(OBJS)
	@echo "→ Edition de liens de $(TARGET)"
	$(CXX) $(OBJS) $(GLAD_OBJ) $(GLFW_LIB) $(LDFLAGS) -o $@

$(OBJS_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "→ Compilation de $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLFW_DEP_DIR):
	@echo "→ Download of GLFW"
	@mkdir -p $(LIB_DIR)
	git clone --depth=1 --branch 3.4 git@github.com:glfw/glfw.git $(LIB_DIR)/glfw
$(GLFW_LIB): $(GLFW_DEP_DIR)
	@echo "→ Compilation of GLFW"
	@mkdir -p $(GLFW_BUILD_DIR)
	@cd $(GLFW_BUILD_DIR) && cmake -DBUILD_SHARED_LIBS=OFF ../../$(LIB_DIR)/glfw && make -s

$(GLAD_BUILD_DIR):
	@echo "→ Download of GLAD generator"
	python3 -m venv .venv
	.venv/bin/pip install glad --quiet
	@echo "→ Generating GLAD files"
	.venv/bin/glad --profile core --api gl=4.6 --generator c --out-path $(GLAD_BUILD_DIR)
$(GLAD_OBJ): $(GLAD_BUILD_DIR)
	@mkdir -p $(OBJS_DIR)
	@echo "→ Compilation of GLAD"
	$(CXX) -I$(GLAD_BUILD_DIR)/include -c $(GLAD_BUILD_DIR)/src/glad.c -o $@

clean:
	@echo "→ Nettoyage..."
	rm -rf $(OBJS_DIR)

lclean: clean
	@echo "→ Nettoyage des librairies..."
	rm -rf $(LIB_DIR)

fclean: lclean
	@echo "→ Nettoyage complet"
	rm -rf .venv
	rm -rf $(BUILD_DIR)/
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fullclean fclean re
