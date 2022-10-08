#include "XPlay2.h"

#include <QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"

int main(int argc, char *argv[])
{
    ///����XDemux
    XDemux demux;

    //�������
    const char *url = "rtmp://mobliestream.c3tv.com:554/live/goodtv.sdp";
    //url = "v1080.mp4";
    cout<<"demux.Open = "<<demux.Open(url);
    cout << "CopyVPara = " << demux.CopyVPara() << endl;
    cout << "CopyAPara = " << demux.CopyAPara() << endl;
    for (;;)
    {
        AVPacket *pkt = demux.Read();
        if (!pkt)break;
    }
    QApplication a(argc, argv);
    XPlay2 w;
    w.show();
    return a.exec();
}
