TARGET = $(BIN_DIR)/list
OBJS = list.o 

LIB = $(BUILD_DIR)/liblist.a
LIB_OBJS = list.o

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
