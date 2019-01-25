/*
 * Image.h
 *
 *  Created on: Jan 22, 2019
 *      Author: ibrahim
 */


#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdlib.h>
#include <string.h>

class Image {
private:
	int height;
	int width;
	int channels;
	double *data;

public:
	Image(int h, int w, int c); // make image
	virtual ~Image(); // free image data

	void zero_image(Image m);
	void zero_channel(Image m, int c);

	/* Show image */
	void show_image(Image p, char* name);
	void show_image_layers(Image p, char* name);

	/* Handling image */
	Image make_random_image(int h, int w, int c);
	// Image make_random_kernel(int size, int c);
	Image copy_image(Image p);
	Image load_image(char* filename);
	Image get_image_layer(Image m, int l); // get input image of layer l

	/* Handling pixels */
	double get_pixel(Image m, int x, int y, int c);
	double get_pixel_extend(int x, int y, int c);
	void set_pixel(Image m, int x, int y, int c, double val);
	void set_pixel_extend(Image m, int x, int y, int c, double val);
	void add_pixel(Image m, int x, int y, int c, double val);
	void add_pixel_extend(Image m, int x, int y, int c, double val);

	// Convolving
	void two_d_convolve(int mc, Image kernel, int kc, int stride, Image out, int oc);
	void convolve(Image kernel, int stride, int channel, Image out);

};

#endif /* IMAGE_H_ */