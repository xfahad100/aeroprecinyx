#ifndef HUD_H
#define HUD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class HUD
{
public:
    HUD( QGraphicsView *gv );
    ~HUD();
    void setVisible(bool vis);
    bool getVisible();
    void show();
    void hide();

private:

    QGraphicsScene* hudScene;
    QGraphicsView* hudView;
    QPixmap* hudBasePixmap;
    bool visible;


};

#endif // HUD_H
