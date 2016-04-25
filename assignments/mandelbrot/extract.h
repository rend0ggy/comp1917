// extract.h
// funtions and types used by extract.c
// richard buckland
// 13 April 2014
// do not alter or submit this file, 
// we'll use our own copy when marking it
 
typedef struct _triordinate {
   double x;
   double y;
   int z;
} triordinate;
 
 
triordinate extract (char *message);
 
double myAtoD (char *message);
 
long myAtoL (char *message);

/*triordinate extract (char *message)
{
	struct triordinate position;
	
	strcpy(position.x,1.1);
	strcpy(position.y,2.2);
	strcpy(position.z,3);
	
	return position;
}*/