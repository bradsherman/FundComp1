// Brad Sherman
// Fundamentals of Computing 1
// Final Project
// Header file for Donkey Kong

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

void drawMario( int, int, int );
void drawmarioHead( int, int, int );
void drawmarioHeads( int, int );
void drawKong( int, int, int );
void drawPeach( int, int, int );
void drawRails( double, double, double, int );
void drawLadders( double, double, double, int, double );
void moveRight( struct Mario_s *, int, int, double, int, double );
void moveLeft( struct Mario_s *, int, int );
void moveUp( struct Mario_s *, int, int, int, double, double );
void checkPosition( struct Mario_s *, double, double, double, double, double, int );
void ladderMovement( struct Mario_s *, int, int, double, double, double );
void jump( struct Mario_s *, double );
void checkFall( struct Mario_s *, double, int*, int, int, int, double);
void drawBarrels( struct Barrel_s*, int, double, double, int, double, double, int* );
void drawBarrel( struct Barrel_s );
void barrelFall( struct Barrel_s*, double, double, double, int, double, int*, int );
int checkCollision( struct Mario_s *, struct Barrel_s, int );
char startScreen( int );
void initializeKong( struct Kong_s *, int, int );
void initializeMario( struct Mario_s *, int, int, int );
void initializeBarrels( struct Barrel_s *, struct Kong_s *, int, int, int, double, double );
void initializePeach( struct Peach_s *, int, int, int , int );
char pauseGame( int, int, char );
void winScreen( int, int );
void loseScreen( int, int );
void decreaseLives( struct Mario_s *, struct Barrel_s *, int, int, int ); 
double returnHeight( struct Mario_s *, int, int, int, double );

