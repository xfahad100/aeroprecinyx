#ifndef HUD_H
#define HUD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include <math.h>

class HUD
{
public:
    HUD( QGraphicsView *gv );
    ~HUD();
    void setVisible(bool vis);
    bool getVisible();
    void show();
    void hide();
    void update();
    inline void setPitch( double p ) { pitch = (float)p; }
    void setRoll( double r ) { roll = (float)r; }
    void setAlpha( double a ) { alpha = (float)a; }

private:

    QGraphicsScene* hudScene;
    QGraphicsView* hudView;
    QPixmap hudBasePixmap;
    QPixmap horizonPixmap;
    QPixmap fpmPixmap;
    QGraphicsPixmapItem* horizonItem;
    QGraphicsPixmapItem* fpmItem;
    QPoint horizonStartPos;
    QPoint fpmStartPos;
    bool visible;
    float pitch;
    float roll;
    float alpha;
    float ppd;
    double DEG2RAD;

};

#endif // HUD_H
