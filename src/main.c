#include <stb_image.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "error: not enough or too many arguments\n");
		fprintf(stdout, "usage: koita [image file]\nor:    koita [image file] [character width in pixels]\n");
		return 1;
	}

	const char *file = argv[1];
	const uint32_t char_width = atoi(argv[2]);
	if (char_width > 16) {
		fprintf(stderr, "error: character width must not exceed 16 pixels\n");
		return 1;
	}

	int32_t pixels_width, pixels_height, pixels_channels; 
	uint8_t *pixels = stbi_load(file, &pixels_width, &pixels_height, &pixels_channels, 0);

	if (!pixels) {
		fprintf(stderr, "error: cannot load image from file: %s\n", file);
		return 1;
	}

	const uint32_t pixels_size = pixels_width * pixels_height;
	const uint32_t pixels_width_scaled = pixels_width / char_width;
	const uint32_t bytes_per_char = char_width * pixels_channels;

	const char *ascii = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
	const double normalisation_constant = (double)pixels_channels * 255 / strlen(ascii);

	for (uint32_t i = 0; i < pixels_size; i += char_width) {
		uint32_t mean_brightness = 0;
		for (uint32_t y = 0; y < bytes_per_char; ++y) {
			for (uint32_t x = 0; x < bytes_per_char; ++x)
				mean_brightness += pixels[(i * pixels_channels) + (x + y * bytes_per_char)];
		}
		mean_brightness /= (bytes_per_char * bytes_per_char); // get the mean

		uint32_t normalised = mean_brightness / normalisation_constant;
		putchar(ascii[normalised]);

		if ((i + char_width) % pixels_width_scaled == 0) {
			putchar('\n');

			i += (char_width /*-1*/) * pixels_width;
		}
	}

	stbi_image_free(pixels);

	return 0;
}
