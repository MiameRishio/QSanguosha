#ifndef CARDITEM_H
#define CARDITEM_H

#include "card.h"
#include "pixmap.h"
#include "QAbstractAnimation"

#include <QSize>

class FilterSkill;
class General;

class CardItem : public Pixmap
{
    Q_OBJECT

public:
    CardItem(const Card *card);
    CardItem(const QString &general_name);

    void filter(const FilterSkill *filter_skill);
    const Card *getFilteredCard() const;

    const Card *getCard() const;
    void setHomePos(QPointF home_pos);
    QPointF homePos() const;
    QAbstractAnimation* goBack(bool kieru = false,bool fadein = true,bool fadeout = true);
    const QPixmap &getSuitPixmap() const;
    const QPixmap &getNumberPixmap() const;
    const QPixmap &getIconPixmap() const;
    void setFrame(const QString &frame);
    void hideFrame();
    void setAutoBack(bool auto_back);
    void changeGeneral(const QString &general_name);
    void writeCardDesc(QString card_owner);
    void deleteCardDesc();

    enum CornerType{
        TopRight,
        BottomRight
    };

    void showAvatar(const General *general, CornerType type = BottomRight);

    void select();
    void unselect();
    bool isPending() const;
    bool isEquipped() const;

    void setFrozen(bool is_frozen);
    bool isFrozen() const;

    static const int NormalY = 36;
    static const int PendingY = NormalY - 40;
    static CardItem *FindItem(const QList<CardItem *> &items, int card_id);

public slots:
    void reduceZ();
    void promoteZ();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);    

private:
    const Card *card, *filtered_card;
    QPixmap suit_pixmap, icon_pixmap, number_pixmap, cardsuit_pixmap;
    QPointF home_pos;
    QGraphicsPixmapItem *frame, *avatar;
    bool auto_back, frozen;
    QString desc;

signals:
    void toggle_discards();
    void clicked();
    void double_clicked();
    void thrown();
    void released();
};

#endif // CARDITEM_H
