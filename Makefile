CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -Werror -pthread -fsanitize=thread
SRCS = t0.cpp \
       t1.cpp \
       thread_create.cpp \
       thread_create_simple_args.cpp \
       thread_create_with_return_args.cpp \
       join_spin.cpp \
       join_no_lock.cpp \
       join_no_state_var.cpp \
       join.cpp \
       join_modular.cpp \
       pc_single_cv.cpp \
       pc.cpp
TARGETS = $(SRCS:.cpp=)

.PHONY: clean

all: $(TARGETS)

$(TARGETS): % : %.o pthread-wrappers.o
	$(CXX) $(CXXFLAGS) -o $@ $^

pthread-wrappers.o: pthread-wrappers.cpp pthread-wrappers.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGETS)
