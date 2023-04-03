
#include "groupbookmark.h"
#include <QPainter>
#include <QEvent>

namespace time_line {

GroupBookMark::GroupBookMark(const DrawWidgetDesc& desc, QWidget *parent)
    : DrawElementWidget(desc,parent){}

QString GroupBookMark::generateDescription() {
    QString res;
    auto last_bkmrk = std::min(desc_draw.idxs.size(),size_t(15));
    for(int i = 0; i < last_bkmrk;i++){
        res+="Bookmark "+QString::number(desc_draw.idxs[i])+"\n";
    }
    return res;
}

QString GroupBookMark::getName() {
    return QString::number(desc_draw.idxs.size());
}

QPalette GroupBookMark::getPalette() {
    QPalette lightPalete = palette();
    lightPalete.setColor(QPalette::Text, Qt::white);
    lightPalete.setColor(QPalette::Button, QColor(255, 87, 51));
    return lightPalete;
}

} // namespace time_line
