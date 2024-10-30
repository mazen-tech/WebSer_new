CC = c++
CFLAGS = -Wall -Wextra -Werror
# SRCS = src/main.cpp
# SRCS = src/main_jp_test.cpp
SRCS = src/main_content_length.cpp \
		src/methods/method_get.cpp \
		src/methods/method_post.cpp \
		src/methods/method_delete.cpp \
		src/server_config/read_conf.cpp \
		src/server_config/server.cpp \
		src/server_config/find_file.cpp \
		src/errors/ErrorPage.cpp

OBJDIR = obj
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

EXEC = WebServer

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
