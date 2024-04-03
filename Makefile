SRCS = get_filetype_readdir.c \
			 get_filetype_stat.c

OBJS = $(SRCS:.c=.o)

BINS = $(SRCS:.c=)

all: $(BINS)

get_filetype_readdir: get_filetype_readdir.o
	$(CC) -o $@ $^
get_filetype_stat: get_filetype_stat.o
	$(CC) -o $@ $^

clean:
	rm -f $(BINS) $(OBJS)
