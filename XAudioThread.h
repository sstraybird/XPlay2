#ifndef XAUDIOTHREAD_H
#define XAUDIOTHREAD_H


#include <QThread>
#include <mutex>
#include <list>
struct AVCodecParameters;
class XDecode;
class XAudioPlay;
class XResample;
class AVPacket;
class XAudioThread :public QThread
{
public:

	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para, int sampleRate, int channels);
	virtual void Push(AVPacket *pkt);
	void run();
	XAudioThread();
	virtual ~XAudioThread();

	//������
	int maxList = 100;
	bool isExit = false;
protected:

	std::list <AVPacket *> packs;
	std::mutex mux;
	XDecode *decode = 0;
	XAudioPlay *ap = 0;
	XResample *res = 0;

};

#endif // XAUDIOTHREAD_H
