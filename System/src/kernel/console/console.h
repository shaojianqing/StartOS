
typedef struct Console Console;

struct Console {

	byte *buffer;

	u32 width;

	u32 height;

	u32 currentX;

	u32 currentY;

	void (*clear)(Console *this);

	void (*print)(Console *this, char *message, char color);

};

void initConsoleSetting();
