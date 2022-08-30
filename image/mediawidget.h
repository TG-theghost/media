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
//#include <QObject>
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


    void on_toolButton_clicked();


    void on_playSlider_valueChanged(int value);

    void on_playpositionchanged(int value);

    void on_playSlider_sliderMoved(int position);

    void on_playSlider_sliderPressed();

    void on_playSlider_sliderReleased();

private:
    Ui::Widget *ui;
    QMediaPlayer* mediaplayer;
    QMediaPlaylist* mediaplaylist;
    QVideoWidget* videowidget;
    int i=1;
    bool n=true;
};

#endif // MEDIAWIDGET_H
