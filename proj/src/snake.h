
#define SEG_HEIGHT 16
#define SEG_WIDTH 16

typedef struct segment segment;

struct segment{
	unsigned short line, col;
	segment *next;
	segment *before;
	unsigned short direction;
};


typedef struct {
	segment *head;
	segment *tail;
	unsigned int size;
	unsigned short boost;
}snake;

int new_snake(int size, unsigned short x, unsigned short y);
