#include "mediawidget.h"
#include "ui_mediawidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("某不愿透露姓名的播放器");//title
    mediaplayer=new QMediaPlayer;
    mediaplaylist=new QMediaPlaylist;
    videowidget=new QVideoWidget(ui->label);
    ui->label->setStyleSheet("background-color:rgb(255,255,255)");//label界面style
    mediaplayer->setPlaylist(mediaplaylist);
    mediaplayer->setVideoOutput(videowidget);
    connect(mediaplayer,&QMediaPlayer::positionChanged,this, &Widget::on_playpositionchanged);


    ui->label->installEventFilter(this);//绑定过滤器

}

Widget::~Widget()
{
    delete ui;
}


bool Widget::eventFilter(QObject *obj,QEvent *eve){//双击全屏,再双击恢复
    if(obj == ui->label){
        if(eve->type()==QEvent::MouseButtonDblClick){
            dblclick++;
            if(dblclick%2==1){
                rect0=ui->label->geometry();
                ui->label->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
                ui->label->showFullScreen();

            }
            else{
                ui->label->setWindowFlags(Qt::SubWindow);
                ui->label->showNormal();
                ui->label->setGeometry(rect0);
            }
        }
        return QObject::eventFilter(obj,eve);
    }
}
void Widget::on_pushButton_clicked()//打开文件按钮
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,"打开文件","C:/Users","allfiles(*.*);;""mp3(*.mp3);;""mp4(*.mp4);;""mkv(*.mkv)");
    ui->listWidget->addItems(filenames);
    foreach(QString const & name,filenames)
    {

        QUrl url(name);
        mediaplaylist->addMedia(url);

    }
    i=1;
}
void Widget::on_toolButton_clicked()//播放按钮
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
void Widget::on_playSlider_valueChanged(int value)//进度条
{
    //qint64 t=mediaplayer->duration();
  // mediaplayer->setPosition(t*value/100);
}
void Widget::on_playpositionchanged(int value)
{
    if(n==true){
        qint64 t=mediaplayer->duration();
        qDebug ("%d %d",value,t);
        if(t!=0)
        {
            qint64 nx=100*value/t;
            ui->playSlider->setValue(nx);
            qDebug ("%d",nx);
        }
    }


}
void Widget::on_playSlider_sliderMoved(int position)
{
    qint64 t=mediaplayer->duration();
   mediaplayer->setPosition(t*position/100);
}
void Widget::on_playSlider_sliderPressed()
{
    n=false;
}
void Widget::on_playSlider_sliderReleased()
{
    n=true;
}
