
#include "groupbookmark.h"
#include <QPainter>
#include <QEvent>

namespace time_line {

GroupBookMark::GroupBookMark(const TimeLineItem& desc, QWidget *parent)
    : DrawElementWidget(desc,parent){}

QString GroupBookMark::getDescription() {
    QString res;
    auto last_bkmrk = desc_draw.bkmrks_idxs.size()>15? 15: desc_draw.bkmrks_idxs.size();
    int i = 0;
    for(i = 0; i < last_bkmrk;i++){
        res+="Bookmark "+QString::number(desc_draw.bkmrks_idxs[i])+"\n";
    }
    if (i < desc_draw.bkmrks_idxs.size()) {
        res+="+ "+QString::number(desc_draw.bkmrks_idxs.size() - i)+" other bookmarks";
    }
    return res;
}

QString GroupBookMark::getName() {
    return QString::number(desc_draw.bkmrks_idxs.size());
}

QPalette GroupBookMark::getPalette() {
    QPalette lightPalete = palette();
    lightPalete.setColor(QPalette::Text, Qt::white);
    lightPalete.setColor(QPalette::Button, QColor(255, 87, 51));
    return lightPalete;
}

} // namespace time_line
