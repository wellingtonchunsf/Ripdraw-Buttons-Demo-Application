/* 
  sampleloader.h
  header fil


*/
#define IMAGE_NAME_LENGTH 30	/* maximun size of ascii file name length */
#define STATUS_OK 0
#define OFF 0
#define ON  1

	/* image_object with info to load, write and manipulate the image */
	struct image_object	
	{
		char image_name[IMAGE_NAME_LENGTH];	/* ascii name of image */
		int image_layer;			/* layer number for image */
		int image_x;				/* X position for image */
		int image_y;				/* Y position for image */
		int image_id;				/* image id returned from Rd_ImageLoad() */
		int image_write_id;			/* image write id returned from Rd_ImageWrite() */
	};

