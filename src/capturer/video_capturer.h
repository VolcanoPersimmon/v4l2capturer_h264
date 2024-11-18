#ifndef VIDEO_CAPTURER_H_
#define VIDEO_CAPTURER_H_

#include <modules/video_capture/video_capture.h>

#include "args.h"
#include "common/interface/subject.h"
#include "common/v4l2_frame_buffer.h"
#include "common/v4l2_utils.h"

class VideoCapturer {
  public:
    VideoCapturer() = default;
    ~VideoCapturer() {
      raw_buffer_subject_.UnSubscribe();
      frame_buffer_subject_.UnSubscribe();
    };
    '''
    在 C++ 中，虚函数（Virtual Function） 是一种允许子类重写（override）基类函数的成员函数，同时提供 动态多态性 的机制。虚函数是通过在函数声明前加上关键字 virtual 定义的。
    '''
    virtual int fps() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual bool is_dma_capture() const = 0;
    virtual uint32_t format() const = 0;
    virtual Args config() const = 0;
    virtual void StartCapture() = 0;
    virtual rtc::scoped_refptr<webrtc::I420BufferInterface> GetI420Frame() = 0;

    std::shared_ptr<Observable<V4l2Buffer>> AsRawBufferObservable() {
        return raw_buffer_subject_.AsObservable();
    };

    std::shared_ptr<Observable<rtc::scoped_refptr<V4l2FrameBuffer>>> AsFrameBufferObservable() {
        return frame_buffer_subject_.AsObservable();
    };

  protected:
    void NextRawBuffer(V4l2Buffer raw_buffer) { raw_buffer_subject_.Next(raw_buffer); };

    void NextFrameBuffer(rtc::scoped_refptr<V4l2FrameBuffer> frame_buffer) {
        frame_buffer_subject_.Next(frame_buffer);
    };

  private:
    Subject<V4l2Buffer> raw_buffer_subject_;
    Subject<rtc::scoped_refptr<V4l2FrameBuffer>> frame_buffer_subject_;
};

#endif
