#ifndef XDEMUX_H
#define XDEMUX_H

#include <mutex>
struct AVFormatContext;

class XDemux
{
public:

    //打开媒体文件，或者流媒体 rtmp http rstp
    virtual bool Open(const char *url);

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
