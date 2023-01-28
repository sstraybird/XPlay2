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
class TestThread :public QThread
{
public:
	XAudioThread at;
    void Init()
    {
        //香港卫视
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

        cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
        //vdecode.Clear();
        //vdecode.Close();
        //cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;
        //cout << "resample.Open = " << resample.Open(demux.CopyAPara(),false) << endl;

        //XAudioPlay::Get()->channels = demux.channels;
        //XAudioPlay::Get()->sampleRate = demux.sampleRate;

        cout << "XAudioPlay::Get()->Open() = " << XAudioPlay::Get()->Open()<<endl;

		cout << "at.Open = " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels);
		at.start();

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
                vdecode.Send(pkt);
                AVFrame *frame = vdecode.Recv();
				if (frame != nullptr) {
					cout << "frame pts" << frame->pts << endl;
				}

                video->Repaint(frame);
                msleep(40);
                //cout << "Video:" << frame << endl;
            }
            if (!pkt)break;
        }
    }
    ///测试XDemux
    XDemux demux;
    ///解码测试
    XDecode vdecode;
    XDecode adecode;
    XResample resample;
    XVideoWidget *video;

};


int main(int argc, char *argv[])
{
    TestThread tt;
    tt.Init();

    QApplication a(argc, argv);
    XPlay2 w;
    w.show();

    //初始化gl窗口
    w.getVideo()->Init(tt.demux.width,tt.demux.height) ;

    tt.video = w.getVideo();
    tt.start();
    return a.exec();
}
