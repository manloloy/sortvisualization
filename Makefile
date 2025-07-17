CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
OBJDIR = obj
TARGET = sortvisualizer

SRC = main.cpp AppManager.cpp SelectionScreen.cpp SortScreen.cpp Button.cpp SortPanel.cpp SelectionSortPanel.cpp InsertionSortPanel.cpp QuickSortPanel.cpp MergeSortPanel.cpp SortRushScreen.cpp
OBJ = $(SRC:.cpp=.o)

SRC_PATHS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ_PATHS = $(addprefix $(OBJDIR)/, $(OBJ))

all: $(TARGET)

$(TARGET): $(OBJ_PATHS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r sortvisualizer;rm -rf $(OBJDIR) $(TARGET)

