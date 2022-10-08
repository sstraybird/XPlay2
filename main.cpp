#include "XPlay2.h"

#include <QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"

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
    url = "001111.mp4";
    cout<<"demux.Open = "<<demux.Open(url);
    cout << "CopyVPara = " << demux.CopyVPara() << endl;
    cout << "CopyAPara = " << demux.CopyAPara() << endl;
    cout << "seek=" << demux.Seek(0.95) << endl;
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
