#ifndef XDEMUX_H
#define XDEMUX_H

#include <mutex>
struct AVFormatContext;
struct AVPacket;

class XDemux
{
public:

    //打开媒体文件，或者流媒体 rtmp http rstp
    virtual bool Open(const char *url);

    //空间需要调用者释放 ，释放AVPacket对象空间，和数据空间 av_packet_free
    virtual AVPacket *Read();

    XDemux();
    virtual ~XDemux();

    //媒体总时长（毫秒）
    int totalMs = 0;
protected:
    std::mutex mux;
    //解封装上下文
    AVFormatContext *ic = NULL;
    //音视频索引，读取时区分音视频
    int videoStream = 0;
    int audioStream = 1;
};

#endif // XDEMUX_H
