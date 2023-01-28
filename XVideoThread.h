#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H


///�������ʾ��Ƶ
struct AVPacket;
struct AVCodecParameters;
class XDecode;
#include <list>
#include <mutex>
#include <QThread>
#include "IVideoCall.h"
class XVideoThread :public QThread
{
public:
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para, IVideoCall *call, int width, int height);
	virtual void Push(AVPacket *pkt);
	void run();

	XVideoThread();
	virtual ~XVideoThread();
	//������
	int maxList = 100;
	bool isExit = false;
protected:
	std::list <AVPacket *> packs;
	std::mutex mux;
	XDecode *decode = 0;
	IVideoCall *call = 0;


};

#endif // XVIDEOTHREAD_H
