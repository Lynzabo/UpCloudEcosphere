#ifndef MOVEGROUPSEQUENCERUNNABLE_H
#define MOVEGROUPSEQUENCERUNNABLE_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"

class BASALOPERAIREMOTEUISHARED_EXPORT MoveGroupSequenceRunnable : public QRunnable
{
public:
    MoveGroupSequenceRunnable(QObject* object = 0);
    /**
     * @brief setMoveInfo
     * @param params
     *        包含参数如下
     *                    opera_type   1 节点到组内  2 节点到组外 3 服务器组到组内  4 服务器组到组外
     *                    x_uuid       操作移动UUID
     *                    x_groupUuid  操作移动GROUPUUID
     *                    y_uuid       移至目标位置的UUID
     *                    y_groupUuid   移至目标位置的GROUPUUID
     *                    x_sequence   操作移动的sequence
     *                    y_sequence   移至目标位置的sequence
     */
    void setMoveInfo(const QVariantMap &params);
protected:
    void run();
private:
    QObject *m_object;
    QVariantMap m_params;
    QString m_cbMsg;
    qint32 m_cbMsgId;
};

#endif // MOVEGROUPSEQUENCERUNNABLE_H
