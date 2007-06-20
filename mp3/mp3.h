#ifndef __MP3_H
#define __MP3_H

/*
 * Praat wrappers for libMAD (MPEG Audio Decoder)
 * Copyright 2007 Erez Volk
 */

#include <sys/types.h>
#include <stdio.h>

/* The following function is used to identify MP3 files */
int mp3_recognize (int nread, const char *data);

/* Actual decoding is done with an MP3_FILE object */
typedef struct _MP3_FILE *MP3_FILE;

typedef int MP3F_SAMPLE;
#if defined (_OFF_T) || defined (__off_t_defined)
	typedef off_t MP3F_OFFSET;
#else
	typedef unsigned long MP3F_OFFSET;
#endif

#define MP3F_MAX_CHANNELS 2
#define MP3F_MAX_SAMPLES  1152 /* Per callback */

typedef void (*MP3F_CALLBACK) (
		const MP3F_SAMPLE *channels[MP3F_MAX_CHANNELS],
		long num_samples,
		void *context);

MP3_FILE mp3f_new (void);
void mp3f_delete (MP3_FILE mp3f);

void mp3f_set_file (MP3_FILE mp3f, FILE *f);

int mp3f_analyze (MP3_FILE mp3f);
unsigned mp3f_channels (MP3_FILE mp3f);
unsigned mp3f_frequency (MP3_FILE mp3f);
MP3F_OFFSET mp3f_samples (MP3_FILE mp3f);

void mp3f_set_callback (MP3_FILE mp3f,
		MP3F_CALLBACK callback, void *context);
int mp3f_seek (MP3_FILE mp3f, MP3F_OFFSET sample);
int mp3f_read (MP3_FILE mp3f, MP3F_OFFSET num_samples);

#define mp3f_sample_to_float(s) ((float)((s) / (float)(1L << 28)))
short mp3f_sample_to_short (MP3F_SAMPLE sample);

#endif /* __MP3_H */

