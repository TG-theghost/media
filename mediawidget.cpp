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
    minimediaplayer=new QMediaPlayer;
    minivideowidget=new QVideoWidget(ui->miniviewlable);
    mediaplayer->setPlaylist(mediaplaylist);
    mediaplayer->setVideoOutput(videowidget);
    minimediaplayer->setPlaylist(mediaplaylist);
    minimediaplayer->setVideoOutput(minivideowidget);

    minimediaplayer->setMuted(true);
    ui->label->setStyleSheet("background-color:rgb(255,255,255)");//label界面style


    connect(mediaplayer,&QMediaPlayer::positionChanged,this, &Widget::on_playpositionchanged);
    mediaplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    ui->voiceSlider->hide();
    //ui->miniviewlable->setStyleSheet("background-color:rgb(0,0,0)");
    ui->miniviewlable->hide();
    ui->voicebtn->setMouseTracking(true);//打开鼠标追踪
    ui->playSlider->setMouseTracking(true);
    ui->vcwidget->setMouseTracking(true);
    ui->playSlider->setMouseTracking(true);
    ui->playslidewidget->setMouseTracking(true);
    ui->label->setMouseTracking(true);

    ui->label->installEventFilter(this);//绑定过滤器
    ui->voicebtn->installEventFilter(this);
    ui->vcwidget->installEventFilter(this);
    ui->playSlider->installEventFilter(this);
    ui->playslidewidget->installEventFilter(this);
    ui->label->installEventFilter(this);


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
                qDebug()<<"233";
                rect0=ui->label->geometry();
                ui->label->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
                ui->label->showFullScreen();
                videowidget->resize(ui->label->size());

            }
            else{
                ui->label->setWindowFlags(Qt::SubWindow);
                ui->label->showNormal();
                ui->label->setGeometry(rect0);
                videowidget->resize(ui->label->size());
            }
        }


    }
    if(obj == ui->voicebtn){
        if(eve->type()==QEvent::MouseMove){
             ui->voiceSlider->show();
             ui->miniviewlable->hide();
             hide=1;


        }


    }
    if(obj == ui->vcwidget){
        if(eve->type()==QEvent::MouseMove)
        {
             int x=ui->vcwidget->mapFromGlobal(QCursor().pos()).x();
             int y=ui->vcwidget->mapFromGlobal(QCursor().pos()).y();

             //qDebug()<<x<<y;
             if(10>x||x>200||10>y||y>50)

                         {
                             ui->voiceSlider->hide();
                             hide=0;
                         }
        }
    }
    if(obj == ui->playSlider){
        if(eve->type()==QEvent::MouseMove)
        {
             int x=ui->playSlider->mapFromGlobal(QCursor().pos()).x();
             int y=ui->playSlider->mapFromGlobal(QCursor().pos()).y();

             //qDebug()<<x<<y;

             if(x-80<0)
             {
                 ui->miniviewlable->setGeometry(10,349,160,90);
             }
             else if(x+80>800)
             {
                 ui->miniviewlable->setGeometry(650,349,160,90);
             }
             else
             {
                  ui->miniviewlable->setGeometry(x-80,349,160,90);
             }

             //ui->miniviewlable->setStyleSheet("background-color:rgb(0,0,0)");
             if(hide!=1)
             {
                 ui->miniviewlable->show();
                 minimediaplayer->play();
                 qint64 t=mediaplayer->duration();
                 minimediaplayer->setPosition(x*t/800);
                 minivideowidget->resize(ui->miniviewlable->size());
                 minimediaplayer->pause();
             }



        }
    }
    if(obj == ui->playslidewidget){
        if(eve->type()==QEvent::MouseMove){
            int x=ui->playslidewidget->mapFromGlobal(QCursor().pos()).x();
            int y=ui->playslidewidget->mapFromGlobal(QCursor().pos()).y();
            if(x<750||x>810)
            {
                ui->voiceSlider->hide();
                hide=0;
            }
            if(x<10||x>810||y<450||y>472)
            {
                ui->miniviewlable->hide();
            }



        }


    }

     return QObject::eventFilter(obj,eve);
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
    mediaplayer->play();
    videowidget->resize(ui->label->size());
    mediaplayer->pause();
}
void Widget::on_toolButton_clicked()//播放按钮
{
    if(i==1)
    {
        mediaplayer->play();
        videowidget->resize(ui->label->size());
        ui->toolButton->setIcon(QIcon(":/image/pause.png"));
        ui->toolButton->setIconSize(QSize(60,60));
        i=0;
    }
    else if(i==0)
    {
        mediaplayer->pause();
        videowidget->resize(ui->label->size());
        ui->toolButton->setIcon(QIcon(":/image/播放.png"));
        ui->toolButton->setIconSize(QSize(60,60));
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
        //qDebug ("%d %d",value,t);
        if(t!=0)
        {
            qint64 nx=100*value/t;
            ui->playSlider->setValue(nx);
           // qDebug ("%d",nx);
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



void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //qDebug()<< item->

}




void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{

}

void Widget::on_voicebtn_clicked()
{
    if(muted==0)
    {
        mediaplayer->setMuted(true);
        muted=1;
    }
    else
    {
        mediaplayer->setMuted(false);
        muted=0;
    }





}

void Widget::on_voiceSlider_valueChanged(int value)
{
    mediaplayer->setVolume(value);
}

void Widget::on_nextbtn_clicked()
{
    mediaplaylist->next();
}

void Widget::on_lastbtn_clicked()
{
     mediaplaylist->previous();
}

void Widget::on_playmodebtn_clicked()
{
    if(playmode==1)
    {
        ui->playmodebtn->setIcon(QIcon(":/image/random.png"));
        mediaplaylist->setPlaybackMode(QMediaPlaylist::Random);
        playmode=0;

    }
    else
    {
        ui->playmodebtn->setIcon(QIcon(":/image/recycle.png"));
        mediaplaylist->setPlaybackMode(QMediaPlaylist::Loop);
        playmode=1;
    }


}
