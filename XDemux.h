#ifndef XDEMUX_H
#define XDEMUX_H

#include <mutex>
struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;
class XDemux
{
public:

    //��ý���ļ���������ý�� rtmp http rstp
    virtual bool Open(const char *url);

    //�ռ���Ҫ�������ͷ� ���ͷ�AVPacket����ռ䣬�����ݿռ� av_packet_free
    virtual AVPacket *Read();

    virtual bool IsAudio(AVPacket *pkt);

    //��ȡ��Ƶ����  ���صĿռ���Ҫ����  avcodec_parameters_free
    AVCodecParameters *CopyVPara();

    //��ȡ��Ƶ����  ���صĿռ���Ҫ���� avcodec_parameters_free
    AVCodecParameters *CopyAPara();

    //seek λ�� pos 0.0 ~1.0
    virtual bool Seek(double pos);

    //��ն�ȡ����
    virtual void Clear();
    virtual void Close();

    XDemux();
    virtual ~XDemux();

    //ý����ʱ�������룩
    int totalMs = 0;
    int width = 0;
    int height = 0;
protected:
    std::mutex mux;
    //���װ������
    AVFormatContext *ic = NULL;
    //����Ƶ��������ȡʱ��������Ƶ
    int videoStream = 0;
    int audioStream = 1;
};

#endif // XDEMUX_H
