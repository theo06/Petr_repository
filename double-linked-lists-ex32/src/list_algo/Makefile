TARGET = $(BIN_DIR)/list_algo
OBJS = list_algo.o
#list_algo_main.o
CFLAGS+= -I../list
#to add -Isrc/list

LIB = $(BUILD_DIR)/liblist_algo.a
LIB_OBJS = list_algo.o

.PHONY : all clean dev lib

all : $(TARGET)
lib : $(LIB)

dev : CFLAGS += -DDEBUG
dev : $(TARGET)

test : CFLAGS += -DDEBUG
test : lib

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(LIB) : CFLAGS += -fPIC
$(LIB) : $(LIB_OBJS)
	ar rcs $@ $(LIB_OBJS)
	ranlib $@

clean :
	rm -f $(LIB) $(LIB_OBJS) $(OBJS) $(TARGET)
