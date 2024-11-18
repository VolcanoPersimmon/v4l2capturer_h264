#ifndef V4L2_CAPTURER_H_
#define V4L2_CAPTURER_H_

#include <modules/video_capture/video_capture.h>

#include "args.h"
#include "capturer/video_capturer.h"
#include "common/interface/subject.h"
#include "common/v4l2_frame_buffer.h"
#include "common/v4l2_utils.h"
#include "common/worker.h"
#include "v4l2_codecs/v4l2_decoder.h"

class V4l2Capturer : public VideoCapturer { //继承自VideoCapturer
  public:
    static std::shared_ptr<V4l2Capturer> Create(Args args);//静态工厂方法
    '''静态工厂方法（Static Factory Method）是一种设计模式，用于通过类的静态方法创建类的实例，而不是直接调用构造函数。它通常返回一个类的实例（可以是原始类型、智能指针、单例实例或其他派生类对象）。'''
    //V4l2Capturer::Create它是一个 static 成员函数，属于类，而不属于某个实例。

    V4l2Capturer(Args args);
    ~V4l2Capturer();
    int fps() const override; //override :重写了基类中的虚函数
    int width() const override;
    int height() const override;
    bool is_dma_capture() const override;
    uint32_t format() const override;
    Args config() const override;
    void StartCapture() override;
    rtc::scoped_refptr<webrtc::I420BufferInterface> GetI420Frame() override;

  private:
    int fd_;
    int fps_;
    int width_;
    int height_;
    int buffer_count_;
    bool hw_accel_;
    bool has_first_keyframe_;
    uint32_t format_;
    Args config_;
    V4l2BufferGroup capture_;
    std::unique_ptr<Worker> worker_;
    std::unique_ptr<V4l2Decoder> decoder_;

    rtc::scoped_refptr<V4l2FrameBuffer> frame_buffer_;
    void NextBuffer(V4l2Buffer &raw_buffer);

    V4l2Capturer &SetFormat(int width, int height);
    V4l2Capturer &SetFps(int fps = 30);
    V4l2Capturer &SetRotation(int angle);

    void Init(std::string device);
    bool IsCompressedFormat() const;
    void CaptureImage();
    bool CheckMatchingDevice(std::string unique_name);
    int GetCameraIndex(webrtc::VideoCaptureModule::DeviceInfo *device_info);
};

#endif
