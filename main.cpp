#include "XPlay2.h"

#include <QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
#include "XDecode.h"
#include "XResample.h"
#include <QThread>
#include "XAudioPlay.h"
#include "XAudioThread.h"
#include "XVideoThread.h"
#include "XDemuxThread.h"
class TestThread :public QThread
{
public:
	XAudioThread at;
    XVideoThread vt;
    void Init()
    {
        //�������
        const char *url = "rtmp://mobliestream.c3tv.com:554/live/goodtv.sdp";
        cout << "demux.Open = " << demux.Open(url);
        demux.Read();
        demux.Clear();
        demux.Close();
        url = "v1080.mp4";
        cout << "demux.Open = " << demux.Open(url);
        cout << "CopyVPara = " << demux.CopyVPara() << endl;
        cout << "CopyAPara = " << demux.CopyAPara() << endl;
        //cout << "seek=" << demux.Seek(0.95) << endl;

        /////////////////////////////

//        cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
        //vdecode.Clear();
        //vdecode.Close();
        //cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;
        //cout << "resample.Open = " << resample.Open(demux.CopyAPara(),false) << endl;

        //XAudioPlay::Get()->channels = demux.channels;
        //XAudioPlay::Get()->sampleRate = demux.sampleRate;

        cout << "XAudioPlay::Get()->Open() = " << XAudioPlay::Get()->Open()<<endl;

		cout << "at.Open = " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels);
        vt.Open(demux.CopyVPara(), video, demux.width, demux.height);
		at.start();
        vt.start();

    }
    unsigned char *pcm = new unsigned char[1024 * 1024];
    void run()
    {
        for (;;)
        {
            AVPacket *pkt = demux.Read();
            if (demux.IsAudio(pkt))
            {
				at.Push(pkt);
                //adecode.Send(pkt);
                //AVFrame *frame = adecode.Recv();
                //int len = resample.Resample(frame, pcm);
                //cout<<"Resample:"<<len<<" ";
                //while (len > 0)
                //{
                //    if (XAudioPlay::Get()->GetFree() >= len)
                //    {
                //        XAudioPlay::Get()->Write(pcm, len);
                //        break;
                //    }
                //    msleep(1);
                //}
                //cout << "Audio:" << frame << endl;
            }
            else
            {
                vt.Push(pkt);
//                vdecode.Send(pkt);
//                AVFrame *frame = vdecode.Recv();
//				if (frame != nullptr) {
//					cout << "frame pts" << frame->pts << endl;
//				}

//                video->Repaint(frame);
//                msleep(40);
                //cout << "Video:" << frame << endl;
            }
            if (!pkt)break;
            if (!pkt)
            {
                demux.Seek(0);
                //break;
            }
        }
    }
    ///����XDemux
    XDemux demux;
    ///�������
//    XDecode vdecode;
//    XDecode adecode;
//    XResample resample;
    XVideoWidget *video=0;

};


int main(int argc, char *argv[])
{
//    TestThread tt;

    QApplication a(argc, argv);
    XPlay2 w;
    w.show();

    //��ʼ��gl����
//    w.getVideo()->Init(tt.demux.width,tt.demux.height) ;

//    tt.video = w.getVideo();
//    tt.Init();

//    tt.start();

    XDemuxThread dt;
	const char *url = "rtmp://mobliestream.c3tv.com:554/live/goodtv.sdp";
	url = "demo2.mp4";
    dt.Open(url, w.getVideo());
    dt.Start();
    return a.exec();
}
