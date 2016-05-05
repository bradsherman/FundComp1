typedef struct Mario_s {
	double xpos;
	double ypos;
	int orientation;
	double dx;
	double dy;
	double vx;
	double vy;
	int width;
	int height;
	int falling;
	int level;
	int lives;
	double xstart;
	double ystart;
	int jump;
	int onLadder;
} Mario;

typedef struct Kong_s {
	double xpos;
	double ypos;
	int orientation;
	int width;
	int height;
	double barrelFreq;
} Kong;

typedef struct Peach_s {
	double xpos;
	double ypos;
	int width;
	int height;
	int orientation;
} Peach;
typedef struct Barrel_s {
	double xpos;
	double ypos;
	double dx;
	double dy;
	double vx;
	double vy;
	double radius;
	int falling;
	int level;
	double xstart;
	double ystart;
} Barrel;
