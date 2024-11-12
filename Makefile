CC = c++
CFLAGS = -ferror-limit=1000 -Wall -Wextra -Werror -std=c++98

SRCS = src/main.cpp \
		src/methods/method_get.cpp \
		src/methods/method_post.cpp \
		src/methods/method_delete.cpp \
		src/methods/save_the_request.cpp \
		src/server_config/read_conf.cpp \
		src/server_config/server.cpp \
		src/server_config/find_file.cpp \
		src/server_config/confParsing.cpp \
		src/error_pages/ErrorPage.cpp \
		src/utils/utils.cpp

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
	rm -rf obj

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
