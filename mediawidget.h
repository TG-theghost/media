#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H
#include <QFileDialog>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QWidget>
#include <QLabel>
#include <QListWidgetItem>
#include <QRect>
#include <QTableWidgetItem>
//#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QTableWidget>
#include <QSize>
#include <QMovie>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include<QMimeData>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void getduration(qint64 playtime);
    void on_pushButton_clicked();
    void on_toolButton_clicked();
    void on_playpositionchanged(int value);
    void on_playSlider_sliderMoved(int position);
    void on_playSlider_sliderPressed();
    void on_playSlider_sliderReleased();
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_voicebtn_clicked();
    void on_voiceSlider_valueChanged(int value);
    void on_nextbtn_clicked();
    void on_lastbtn_clicked();
    void on_playmodebtn_clicked();
    void contextMenuEvent(QContextMenuEvent *eve);
    void ScreenShots();
    void Pause();
    void keyPressEvent(QKeyEvent *eve);
    void speed0();
    void speed1();
    void speed2();



private:
    Ui::Widget *ui;
    QMediaPlayer* mediaplayer;
    QMediaPlaylist* mediaplaylist;
    QVideoWidget* videowidget;
    QMediaPlayer* minimediaplayer;
    QVideoWidget* minivideowidget;
    QStringList filenames;

    int i=1;

    bool n=true;

    int screenshotnum=0;
    int dblclick=0;    //判断双击次数
    bool muted=0;
    bool hide=1;
    bool playmode=1;
    QRect rect0;//全屏定位
    int speednum=1;

    bool eventFilter(QObject *obj,QEvent *eve);//事件过滤器
    void resizeEvent(QResizeEvent *event);//窗口大小改变事件
    void dragEnterEvent(QDragEnterEvent*event);//拖动进入事件
    void dropEvent(QDropEvent*event);//文件拖入处理

};




#endif // MEDIAWIDGET_H
