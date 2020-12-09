#include <stdbool.h>

typedef enum { inter, cub, arr } var_typ;

typedef struct {
	int value; 
} interType;

typedef struct {
	int x;
	int y;
	char z;
} cubType;

typedef struct nodeTypeTag {
	var_typ n_type; /* type of node */
	int label;
	/* union must be last entry in nodeType */
	/* because operNodeType may dynamically increase */
	union {
		interType con; /* constants */
		cubType id; /* identifiers */	
	};
} nodeType;