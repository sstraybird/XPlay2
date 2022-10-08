#include "XPlay2.h"

#include <QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
#include "XDecode.h"
int main(int argc, char *argv[])
{
    ///≤‚ ‘XDemux
    XDemux demux;

    //œ„∏€Œ¿ ”
    const char *url = "rtmp://mobliestream.c3tv.com:554/live/goodtv.sdp";
    cout<<"demux.Open = "<<demux.Open(url) << endl;
    demux.Read();
    demux.Clear();
    demux.Close();
    url = "v1080.mp4";
    cout<<"demux.Open = "<<demux.Open(url);
    cout << "CopyVPara = " << demux.CopyVPara() << endl;
    cout << "CopyAPara = " << demux.CopyAPara() << endl;
    cout << "seek=" << demux.Seek(0.95) << endl;

    XDecode vdecode;
    cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
//    vdecode.Clear();
//    vdecode.Close();
    XDecode adecode;
    cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;


    for (;;)
    {
        AVPacket *pkt = demux.Read();
        if (demux.IsAudio(pkt))
        {
            adecode.Send(pkt);
            AVFrame *frame = adecode.Recv();
            //cout << "Audio:" << frame << endl;
        }
        else
        {
            vdecode.Send(pkt);
            AVFrame *frame = vdecode.Recv();
            //cout << "Video:" << frame << endl;
        }
        if (!pkt)break;
    }
    QApplication a(argc, argv);
    XPlay2 w;
    w.show();
    return a.exec();
}
