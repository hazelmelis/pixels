#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* 
My first goal is to create a framebuffer, fill in the pixels for a green square,
and write that framebuffer to a .bmp file.
*/

#define WIDTH 256
#define HEIGHT 256

/* A bmp header is 54 bytes. 
 
	typedef struct {             // Total: 54 bytes
	  uint16_t  type_0;             // Magic identifier: 0x4d42
	  uint32_t  size_2;             // File size in bytes
	  uint16_t  reserved1_6;        // Not used
	  uint16_t  reserved2_8;        // Not used
	  uint32_t  offset_10;           // Offset to image data in bytes from beginning of file (54 bytes)
	  uint32_t  dib_header_size_14;  // DIB Header size in bytes (40 bytes)
	
	  // The sign of the integer indicates direction.
	  int32_t   width_px_18;         // Width of the image
	  int32_t   height_px_22;        // Height of image
				      //
	  uint16_t  num_planes_26;       // Number of color planes
	  uint16_t  bits_per_pixel_28;   // Bits per pixel
	  uint32_t  compression_30;      // Compression type
	  uint32_t  image_size_bytes_34; // Image size in bytes
				
	  // Resolution can be negative to indicate direction in the coordinate system.
	  int32_t   x_resolution_ppm_38; // Pixels per meter
	  int32_t   y_resolution_ppm_42; // Pixels per meter
				      //
	  uint32_t  num_colors_46;       // Number of colors  
	  uint32_t  important_colors_50; // Important colors 
	} BMPHeader;

	this will be useful later... includes the byte index to use for each variable.

*/
#define HEADER_SIZE 54

// Each pixel is 3 bytes (RGB) we're going old school.
#define BYTES_PER_PIXEL 3



int main(int argc, char* argv[])
{
	// Unsigned 8-bit int because each pixel is a byte.
	// The number of pixels is the total area, bytes per pixel is the size of each pixel "element".
	// calloc initializes all memory to 0, so in this context just black pixels. 
	//
	// void* calloc(size_t number_of_elements, size_t size_of_each_element_in_bytes);
	uint8_t* framebuffer = calloc(WIDTH * HEIGHT, BYTES_PER_PIXEL);
	
	FILE* fp = fopen("square.bmp", "wb");
	if (!fp)
	{
		perror("Failed to open 'square.bmp' for writing: ");
		exit(1); // Will handle this gracefully eventually after a refactor.
	}

	uint32_t file_size = HEADER_SIZE + WIDTH * HEIGHT * BYTES_PER_PIXEL;

	uint8_t header[HEADER_SIZE] = { 0 };

	header[0] = 0x4d42;
	header[14] = HEADER_SIZE;
	header[18] = WIDTH;
	header[22] = HEIGHT;
	header[26] = 1; 	// planes
	header[28] = 24;	// bits per pixel
	
	fwrite(header, 1, HEADER_SIZE, fp);
	fclose(fp);



	free(framebuffer);

	return 0;
}







