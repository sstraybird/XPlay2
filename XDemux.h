#ifndef XDEMUX_H
#define XDEMUX_H

#include <mutex>
struct AVFormatContext;

class XDemux
{
public:

    //��ý���ļ���������ý�� rtmp http rstp
    virtual bool Open(const char *url);

    XDemux();
    virtual ~XDemux();

    //ý����ʱ�������룩
    int totalMs = 0;
protected:
    std::mutex mux;
    //���װ������
    AVFormatContext *ic = NULL;
    //����Ƶ��������ȡʱ��������Ƶ
    int videoStream = 0;
    int audioStream = 1;
};

#endif // XDEMUX_H
