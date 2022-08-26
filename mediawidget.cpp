#include "mediawidget.h"
#include "ui_mediawidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("某不愿透露姓名的播放器");
    mediaplayer=new QMediaPlayer;
    mediaplaylist=new QMediaPlaylist;
    videowidget=new QVideoWidget(ui->label);
    mediaplayer->setPlaylist(mediaplaylist);
    mediaplayer->setVideoOutput(videowidget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,"打开文件","C:/Users/tongw/Desktop","allfiles(*.*);;""mp3(*.mp3);;""mp4(*.mp4);;""mkv(*.mkv)");
    mediaplaylist->clear();
    foreach(QString const & name,filenames)
    {
        QUrl url(name);
        mediaplaylist->addMedia(url);

    }
    i=1;
}

void Widget::on_pushButton_2_clicked()
{
    if(i==1)
    {
        mediaplayer->play();
        videowidget->resize(ui->label->size());
        i=0;
    }
    else if(i==0)
    {
        mediaplayer->pause();
        videowidget->resize(ui->label->size());
        i=1;
    }
}
