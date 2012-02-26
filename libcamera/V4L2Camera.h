/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      Author: Niels Keeman <nielskeeman@gmail.com>
 *
 */

#ifndef _V4L2CAMERA_H
#define _V4L2CAMERA_H

#define NB_BUFFER 2

#include <binder/MemoryBase.h>
#include <binder/MemoryHeapBase.h>
#include <linux/videodev.h>

namespace android {

struct vdIn {
    struct v4l2_capability cap;
    struct v4l2_format format;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers rb;
    void *mem[NB_BUFFER];
    bool isStreaming;
    int width;
    int height;
    int formatIn;
    int framesizeIn;
};

class V4L2Camera {

public:
    V4L2Camera();
    ~V4L2Camera();

    int Open(const char *device);
    void Close();
    int SetFormat(int width, int height, int pixelformat);

    int Init ();
    void Uninit ();

    int setAutofocus(void);
    int getAutoFocusResult(void);
    int cancelAutofocus(void);

    int StartStreaming ();
    int StopStreaming ();

    void GrabPreviewFrame (void *previewBuffer);
    sp<IMemory> GrabRawFrame ();
    sp<IMemory> GrabJpegFrame ();

private:
    struct vdIn *videoIn;
    int fd;

    int nQueued;
    int nDequeued;

    int saveYUYVtoJPEG (unsigned char *inputBuffer, int width, int height, FILE *file, int quality);

    void convert(unsigned char *buf, unsigned char *rgb, int width, int height);
    void yuv_to_rgb16(unsigned char y, unsigned char u, unsigned char v, unsigned char *rgb);
};

}; // namespace android

#endif
