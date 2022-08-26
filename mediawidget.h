#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H
#include <QFileDialog>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QWidget>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer* mediaplayer;
    QMediaPlaylist* mediaplaylist;
    QVideoWidget* videowidget;
    int i=1;
};

#endif // MEDIAWIDGET_H
