#include "mediawidget.h"
#include "ui_mediawidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("某不愿透露姓名的播放器");//title
    this->setAcceptDrops(true);     //设置主界面接受拖动进来的文件
    mediaplayer=new QMediaPlayer;//初始化主显示label
    mediaplaylist=new QMediaPlaylist;
    videowidget=new QVideoWidget(ui->label);
    minimediaplayer=new QMediaPlayer;//初始化预览小型label
    minivideowidget=new QVideoWidget(ui->miniviewlable);
    mediaplayer->setPlaylist(mediaplaylist);
    mediaplayer->setVideoOutput(videowidget);
    minimediaplayer->setPlaylist(mediaplaylist);
    minimediaplayer->setVideoOutput(minivideowidget);
    minimediaplayer->setMuted(true);
   // ui->label->setStyleSheet("background-color:rgb(0,0,0)");//label界面style
    ui->miniviewlable->raise();//提高预览label显示优先级
    this->grabKeyboard();
    connect(mediaplayer,&QMediaPlayer::positionChanged,this, &Widget::on_playpositionchanged);//将播放进度改变与进度条移动连接
    mediaplaylist->setPlaybackMode(QMediaPlaylist::Loop);//默认循环播放
    ui->voiceSlider->hide();//音量默认吟唱
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
    ui->speedBtn->installEventFilter(this);




}

Widget::~Widget()
{
    delete ui;
}


bool Widget::eventFilter(QObject *obj,QEvent *eve){//事件过滤器
    if(obj == ui->label){//双击全屏
        if(eve->type()==QEvent::MouseButtonDblClick){

            dblclick++;
            if(dblclick%2==1){
                //qDebug()<<"233";
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
//        if(eve->type()==QEvent::MouseButtonPress)//鼠标单击暂停，但是由于这样在打开全屏会暂停播放切换导致不连贯所以注释掉
//        {

//            Pause();
//        }


    }
    if(obj == ui->voicebtn){//鼠标悬浮音量显示
        if(eve->type()==QEvent::MouseMove){
             ui->voiceSlider->show();
             ui->miniviewlable->hide();



        }


    }
    if(obj == ui->vcwidget){//鼠标离开关闭音量显示
        if(eve->type()==QEvent::MouseMove)
        {
             int x=ui->vcwidget->mapFromGlobal(QCursor().pos()).x();
             int y=ui->vcwidget->mapFromGlobal(QCursor().pos()).y();
             int y2=(ui->vcwidget->height()-ui->voicebtn->height())/2;
             int y3=ui->vcwidget->height()-y2;
             //qDebug()<<x<<y;

             if(9>x||x>9+ui->voicebtn->width()+ui->voiceSlider->width()||y2>y||y>y3)

                         {
                             ui->voiceSlider->hide();

                         }
        }
    }
    if(obj == ui->playSlider){//鼠标悬浮进度条展示预览内容
        if(eve->type()==QEvent::MouseMove)
        {
             int x=ui->playSlider->mapFromGlobal(QCursor().pos()).x();
             int y=ui->playSlider->mapFromGlobal(QCursor().pos()).y();
             int sx=ui->playSlider->x();
             int sy=ui->playSlider->y();
             int lw=ui->label->width();
             int lh=ui->label->height();
             int lx=ui->label->x();
             int ly=ui->label->y();


             //qDebug()<<x<<y;

             if(x-lw/10<0)
             {
                 ui->miniviewlable->setGeometry(lx,ly+lh-lh/5,lw/5,lh/5);
             }
             else if(x+lw/10>ui->playSlider->width())
             {
                 ui->miniviewlable->setGeometry(lw-lw/5,ly+lh-lh/5,lw/5,lh/5);
             }
             else
             {
                  ui->miniviewlable->setGeometry(x-lw/10,ly+lh-lh/5,lw/5,lh/5);
             }

            // ui->miniviewlable->setStyleSheet("background-color:rgb(0,0,0)");

                 ui->miniviewlable->show();
                 minimediaplayer->play();
                 qint64 t=minimediaplayer->duration();
                 minimediaplayer->setPosition(x*t/ui->playSlider->width());
                 minivideowidget->resize(ui->miniviewlable->size());
                 minimediaplayer->pause();




        }
    }
    if(obj == ui->playslidewidget){//鼠标离开关闭预览
        if(eve->type()==QEvent::MouseMove){
            int x=ui->playslidewidget->mapFromGlobal(QCursor().pos()).x();
            int y=ui->playslidewidget->mapFromGlobal(QCursor().pos()).y();

            int sx=ui->playSlider->x();
            int sy=ui->playSlider->y();
            int sw=ui->playSlider->width();
            int sh=ui->playSlider->height();
            if(x<sx||x>sw+sx||y<sy||y>sy+sh)
            {
                ui->miniviewlable->hide();

            }




        }


    }
    if(obj == ui->speedBtn){//视频播放倍速选择
        if(eve->type()==QEvent::MouseButtonRelease){
            speednum++;
                if(speednum==1){
                    speed0();
                    ui->speedBtn->setText("X1.0");
                }
                if(speednum==2){
                    speed1();
                    ui->speedBtn->setText("X1.5");
                }
                if(speednum==3){
                    speed2();
                    ui->speedBtn->setText("X2.0");
                    speednum=0;
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
void Widget::on_toolButton_clicked()//播放按钮，已用新函数代替
{
//    if(i==1)
//    {
//        mediaplayer->play();
//        videowidget->resize(ui->label->size());
//        ui->toolButton->setIcon(QIcon(":/image/pause.png"));
//        ui->toolButton->setIconSize(QSize(60,60));
//        i=0;
//    }
//    else if(i==0)
//    {
//        mediaplayer->pause();
//        videowidget->resize(ui->label->size());
//        ui->toolButton->setIcon(QIcon(":/image/播放.png"));
//        ui->toolButton->setIconSize(QSize(60,60));
//        i=1;
//    }
    Pause();
}

void Widget::on_playpositionchanged(int value)//该函数在播放进度改变时改变进度条
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
void Widget::on_playSlider_sliderMoved(int position)//该函数在进度条改变时改变播放进度
{
    qint64 t=mediaplayer->duration();
   mediaplayer->setPosition(t*position/100);
}
void Widget::on_playSlider_sliderPressed()//与下一条函数一起保证在拖动进度条过程中进度条不受上方函数控制
{
    n=false;
}
void Widget::on_playSlider_sliderReleased()
{
    n=true;
}

void Widget::on_listWidget_doubleClicked(const QModelIndex &index)//双击播放点击文件
{
   // qDebug()<< index.row();
    mediaplaylist->setCurrentIndex(index.row());

}
void Widget::on_voicebtn_clicked()//单击切换静音
{
    if(muted==0)
    {
        mediaplayer->setMuted(true);
        ui->voicebtn->setIcon(QIcon(":/image/静音.png"));
        muted=1;
    }
    else
    {
        mediaplayer->setMuted(false);
        ui->voicebtn->setIcon(QIcon(":/image/声音.png"));
        muted=0;
    }





}
void Widget::on_voiceSlider_valueChanged(int value)//音量滑条控制音量
{
    mediaplayer->setVolume(value);
}
void Widget::on_nextbtn_clicked()//播放下一个
{
    mediaplaylist->next();
}
void Widget::on_lastbtn_clicked()//播放上一个
{
     mediaplaylist->previous();
}
void Widget::on_playmodebtn_clicked()//切换播放模式为随机或循环
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
void Widget::contextMenuEvent(QContextMenuEvent *eve){//鼠标右击菜单
    QMenu *menu = new QMenu();

    QAction *Clockwise =new QAction(u8"顺时针旋转90°",this);//u8:UTF-8
    QAction *Screenshots = new QAction(u8"屏幕拍照(截图)",this);
    QAction *Pause=new QAction(u8"暂停/播放",this);
    menu->addAction(Clockwise);
    menu->addAction(Screenshots);
    menu->addAction(Pause);

    connect(Clockwise,SIGNAL(triggered(bool)),this,SLOT(ClockWise()));
    connect(Screenshots,SIGNAL(triggered(bool)),this,SLOT(ScreenShots()));
    connect(Pause,SIGNAL(triggered(bool)),this,SLOT(Pause()));
    QPoint menuPos = eve->globalPos();
    menu->exec(menuPos);

}
void Widget::ClockWise(){
    //ui->label->setRotation
    qDebug() << "顺时针旋转90°"<<endl;
}
void Widget::ScreenShots(){//截图功能
    screenshotnum++;

    qDebug() << "截图"<<endl;

    QScreen *screen= QGuiApplication::primaryScreen();
    QPixmap pixmap=screen->grabWindow(ui->label->winId());
    qDebug() << "截个屁图"<<endl;

    QString filePath="F:\\";

    filePath.append("screenshot");


    QString s=QString::number(screenshotnum);
    filePath.append(s);
    filePath.append(".jpg");
     qDebug()<<filePath;
    pixmap.save(filePath,"jpg");

}
void Widget::Pause(){//新函数让点击按钮和右键都可以切换暂停播放
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
void Widget::keyPressEvent(QKeyEvent *eve){//空格暂停
    if(eve->key()==Qt::Key_Space){
        Pause();
       // qDebug()<<"space";
        return ;
    }
    Widget::keyPressEvent(eve);
}
//speed
void Widget::speed0(){//播放速度的几个函数
    qDebug()<<"X1.0"<<endl;
    mediaplayer->setPlaybackRate(1);
}
void Widget::speed1(){
    qDebug()<<"X1.5"<<endl;
    mediaplayer->setPlaybackRate(1.5);
}
void Widget::speed2(){
    qDebug()<<"X2.0"<<endl;
    mediaplayer->setPlaybackRate(2);
}
void Widget::resizeEvent(QResizeEvent *event)//窗口大小改变时重绘播放窗大小
{
     videowidget->resize(ui->label->size());
}
void Widget::dragEnterEvent(QDragEnterEvent* e)//拖动文件过滤器
{

    if (true)
    {
        e->acceptProposedAction();
    }
}
void Widget::dropEvent(QDropEvent* e)//拖动文件后处理事件
{
    const QMimeData*qm=e->mimeData();
    QList<QUrl> urls = e->mimeData()->urls();
    QString qfilenames =qm->urls()[0].toLocalFile();
    ui->listWidget->addItem(qfilenames);
    if(urls.isEmpty())
        return ;
    foreach (QUrl u, urls)
    {
        mediaplaylist->addMedia(u);
    }


}

