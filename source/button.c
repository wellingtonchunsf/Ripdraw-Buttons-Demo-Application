/* 
 * Sample Ripdraw program on how to put up simple images
 *
 * button.c
 *
 * Demo program for Ripdraw Display
 * This program will, 
 *   - enable a layer
 *   - load a image (from Ripdraw flash to graphic memory, images must already be loaded int he Ripdraw flash)
 *   - write the image to a layer 
 *   - compose all the layers, which display it on the Ripdraw Display
 *
 * The program will look at the image_list structure for the
 *    - image name
 *    - layer to write it to
 *    - x position
 *    - y positon
 *    - imageid is for storage of imageid from Rd_ImageLoad()
 *    - imagewrite_id is for storage of imagewrite_id from Rd_ImageWrite()
 * 
 */


#include <stdio.h>
#include "../include/ripdraw.h"
#include "../include/sampleloader.h"

#define ENDLIST 0xff	/* End of list flag in layer field */
#define SLEEPTIME 1000	/* amount of time to sleep so user can see transitions */

#define LAYER_START 1
#define LAYER_END  7

int main(int argc, char **argv)
{
	int i;
	int ii;
	int ret;

	/* load the image_list with the image name, layer, x position, y positon, imageid and imagewrite id, last two are uninitialzied */
	struct image_object image_list[] =
	{
		{"blue-off",		1,		0,0,		0,0},\
		{"blue-on",		1,		0,150,		0,0},\
		{"gold-button",		1,		0,300,		0,0},\
		{"gray-off",		1,		0,450,		0,0},\
		{"green-off",		2,		150,0,		0,0},\
		{"pink-off",		2,		150,150,	0,0},\
		{"red-off",		2,		150,300,	0,0},\
		{"red-on",		2,		150,450,	0,0},\
		{"button-lrb-blue",	3,		300,0,		0,0},\
		{"button-lrb-green",	3,		300,150,	0,0},\
		{"button-lrb-orange",	3,		300,300,	0,0},\
		{"button-lrb-yellow",	3,		300,450,	0,0},\
		{"blue-off",		4,		450,0,		0,0},\
		{"blue-on",		4,		450,150,	0,0},\
		{"gold-button",		4,		450,300,	0,0},\
		{"gray-off",		4,		450,450,	0,0},\
		{"green-off",		5,		600,0,		0,0},\
		{"pink-off",		5,		600,150,	0,0},\
		{"red-off",		5,		600,300,	0,0},\
		{"red-on",		5,		600,450,	0,0},\
		{"button-lrb-blue",	6,		750,0,		0,0},\
		{"button-lrb-green",	6,		750,150,	0,0},\
		{"button-lrb-orange",	6,		750,300,	0,0},\
		{"button-lrb-yellow",	6,		750,450,	0,0},\
		{"blue-off",		7,		900,0,		0,0},\
		{"blue-on",		7,		900,150,	0,0},\
		{"gold-button",		7,		900,300,	0,0},\
		{"gray-off",		7,		900,450,	0,0},\
		{"STOP",ENDLIST,0,0,	0,0}     /* Setting layer = ENDLIST, denotes end of list this must be last entry in list */
	};


	/* RdInterfaceInit()
	 *    Open port on host computer to Ripdraw display
	 *    initialize Ripdraw library by creating a rd_interface handle
	 */
	RD_INTERFACE* rd_interface = RdInterfaceInit("\\\\.\\COM10");

	/* check if verbose is set from command line */
	if (argc > 1)
	{
		rd_interface->verbose = atoi(argv[1]);
		if (rd_interface->verbose < 0)
		{
			rd_interface->verbose = 0;
		}
	}

	/* Issue reset to Ripdraw display */
	ret = Rd_Reset(rd_interface);
	if (ret != STATUS_OK) return ret;

	/* enable layer, load image and write it 
	do this for every element of the list
	stop when element has image_layer = ENDLIST
	*/
	for (i=0; image_list[i].image_layer != ENDLIST; i++)
	{
		ret = enableloadwrite(rd_interface, image_list[i], RD_TRUE, RD_TRUE, RD_TRUE);
		if (ret != STATUS_OK) return ret;
	}
	
	/* compose all layers to page 1 so everything shows up at once */
	ret = Rd_ComposeLayersToPage(rd_interface, 1);
	if (ret != STATUS_OK) return ret;

	/* disable each layer and compose as we go so that you can see it */
	for (i=LAYER_START; i <= LAYER_END;  i++)
	{
		ret = Rd_SetLayerEnable(rd_interface, i ,RD_FALSE); 
		if (ret != STATUS_OK) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
		Sleep(SLEEPTIME);
	
	}

	/* enable each layer and compose as we go so that you can see it */
	for (i=LAYER_START; i <= LAYER_END;  i++)
	{
		ret = Rd_SetLayerEnable(rd_interface, i ,RD_TRUE); 
		if (ret != STATUS_OK) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
		Sleep(SLEEPTIME);
	
	}

	/* disable each layer in reverse order and compose as we go so that you can see it */

	ii= LAYER_END; /* start at end */
	for (i=LAYER_START; i <= LAYER_END;  i++)
	{
		ret = Rd_SetLayerEnable(rd_interface, ii ,RD_FALSE); 
		if (ret != STATUS_OK) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
		Sleep(SLEEPTIME);
		ii--; /* do next layer in reverse order */
	
	}
	/* enable odd layer and compose as we go so that you can see it */
	for (i=LAYER_START; i <= LAYER_END;  i++)
	{
		ret = Rd_SetLayerEnable(rd_interface, i ,RD_TRUE); 
		if (ret != STATUS_OK) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
		Sleep(SLEEPTIME);
		i++; /* skip each odd layer*/	
	}

	/* enable even layer and compose as we go so that you can see it */
	for (i=LAYER_START; i <= LAYER_END;  i++)
	{
		i++; /* skip each even layer*/	
		ret = Rd_SetLayerEnable(rd_interface, i ,RD_TRUE); 
		if (ret != STATUS_OK) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
		Sleep(SLEEPTIME);
	}
	
	/* close off the interface */
	ret = RdInterfaceClose(rd_interface);


	printf("\nRet: %d\n", ret);
	printf("Done!\n");
	return 0;
}
