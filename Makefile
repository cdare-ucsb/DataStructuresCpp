CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Wextra -pedantic \
           -Isrc \
           -Ilib/googletest/googletest/include \
           -Ilib/googletest/googletest
LDFLAGS = -pthread

SRC_DIR = src
TEST_DIR = tests
GTEST_DIR = lib/googletest/googletest

# Default target if you just run `make`
TARGET = driver

# Test target
TEST_TARGETS = test_binary_tree test_hash_table test_prefix_trie


# GoogleTest sources
GTEST_SRC = \
  $(GTEST_DIR)/src/gtest-all.cc \
  $(GTEST_DIR)/src/gtest_main.cc

# Default source (if you just use `make`)
SRC = $(SRC_DIR)/driver.cpp

# Automatically discover modules by finding all src/*/driver.cpp
MODULES := BinaryTree HashTable PrefixTrie MaxHeap

.PHONY: all test clean $(MODULES)

all: $(TARGET)

# Default build (useful if you have a shared top-level driver)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test targets
test: $(TEST_TARGETS)
	@for test_exec in $(TEST_TARGETS); do \
		echo "Running $$test_exec..."; \
		./$$test_exec; \
	done

test_binary_tree: $(TEST_DIR)/test_binary_tree.cpp $(GTEST_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test_hash_table: $(TEST_DIR)/test_hash_table.cpp $(GTEST_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test_prefix_trie: $(TEST_DIR)/test_prefix_trie.cpp $(GTEST_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)


# Rule to build each module (e.g., BinaryTree → src/BinaryTree/driver.cpp)
$(MODULES):
	$(CXX) $(CXXFLAGS) src/$@/driver.cpp -o $@ $(LDFLAGS)

# Clean everything
clean:
	rm -f $(TARGET) $(TEST_TARGETS) $(MODULES)
